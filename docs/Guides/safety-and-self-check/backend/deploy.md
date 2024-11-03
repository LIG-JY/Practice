# 배포

## 준비

### 배포할 EC2에 Docker 설치하기

- https://docs.docker.com/engine/install/ubuntu/

### 배포할 EC2에 AWS CLI 설정

```shell
sudo apt update
sudo apt install -y awscli
```

설치 확인

```shell
aws --version
```

IAM 자격 증명 설정

```shell
aws configure
```

- AWS Access Key ID: IAM 사용자의 액세스 키 ID
- Secret Access Key: IAM 사용자의 비밀 액세스 키
- Default region name: ECR이 위치한 AWS 리전 (예: ap-northeast-2)
- Dault output format: json 또는 text (원하는 형식)

### DockerFile 작성

- /root/web 에 작성
    - web 모듈이 entry point

```dockerfile
# Build stage
# eclipse-temurin:17-jdk 이미지를 기반으로 새 단계(빌드 단계)를 정의, JDK가 포함된 환경을 사용
FROM eclipse-temurin:17-jdk AS builder

# Build context에 전체 소스를 복사
COPY . /app
WORKDIR /app

# Gradle로 build task 실행, -x test 옵션으로 테스트 생략 가능
RUN ./gradlew :web:bootJar -x test

# Runtime stage
# JDK 보다 가벼운 JRE 이미지를 사용해 최종 컨테이너 크기를 줄임
FROM eclipse-temurin:17-jre AS runtime

# 빌드된 JAR 파일을 runtime 이미지로 복사
COPY --from=builder /app/web/build/libs/web-0.0.1-SNAPSHOT.jar app.jar

# 애플리케이션 실행 커맨드
ENTRYPOINT ["java", "-jar", "app.jar"]
```

### Github Action 스크립트 작성

- /root/.github 에 작성

```yaml
name: deploy
# To automatically trigger a workflow, use "on" to define which events can cause the workflow to run
on:
  workflow_dispatch:
    inputs:
      profile:
        required: true
        type: string
        description: 'profile name of spring boot application'
      branch:
        required: true
        type: string
        description: 'branch to deploy'
# A workflow run is made up of one or more "jobs", which run in parallel by default.
jobs:
  # "build" is job_id it is unique identifier
  build:
    # define the type of machine(runner) to run the job on.
    runs-on: ubuntu-latest
    # A job contains a sequence of tasks called "steps". Steps can run commands,
    steps:

      - name: check-out
        # "uses" keyword is used within a "step" and specify it should use "actions"
        uses: actions/checkout@v4 # This action checks-out your repository under $GITHUB_WORKSPACE, so your workflow can access it.
        with:
          ref: ${{ github.event.inputs.branch }}

      - name: set up jdk temurin 17
        uses: actions/setup-java@v4
        with:
          distribution: 'temurin' # See 'Supported distributions' for available options
          java-version: '17'

      - name: build with gradle
        run: |
          chmod +x ./gradlew
          ./gradlew :web:bootJar -x test

      - name: Configure AWS Credentials
        uses: aws-actions/configure-aws-credentials@v3
        with:
          aws-access-key-id: ${{ secrets.AWS_ACCESS_KEY_ID }}
          aws-secret-access-key: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          aws-region: ${{ secrets.AWS_REGION }}

      - name: Login to Amazon ECR
        uses: aws-actions/amazon-ecr-login@v2

      - name: Build Docker Image # -f 옵션으로 경로 지정
        run: |
          echo "Building Docker image..."
          docker build -t ssc-backend -f web/Dockerfile .
          docker tag ssc-backend:latest ${{ secrets[format('{0}_ECR_REPOSITORY_URI', github.event.inputs.profile)] }}:latest
          echo "Docker image tagged as ${{ secrets[format('{0}_ECR_REPOSITORY_URI', github.event.inputs.profile)] }}:latest"

      - name: Push Docker Image to Amazon ECR
        run: |
          echo "Pushing Docker image to Amazon ECR..."
          docker push ${{ secrets[format('{0}_ECR_REPOSITORY_URI', github.event.inputs.profile)] }}:latest
          echo "Docker image pushed successfully."

      - name: Create .env file
        run: |
          echo "SPRING_PROFILES_ACTIVE=${{ github.event.inputs.profile }}" >> .env
          echo "JWT_SECRET_KEY=${{ secrets[format('{0}_jwt_secret', github.event.inputs.profile)] }}" >> .env
          echo "MONGODB_URI=${{ secrets[format('{0}_mongodb_uri', github.event.inputs.profile)] }}" >> .env
          echo "CORS_ALLOWED_ORIGINS=${{ secrets[format('{0}_cors_allowed_origins', github.event.inputs.profile)] }}" >> .env
          echo ".env file created with necessary environment variables."

      - name: Setup SSH Agent for Bastion
        uses: webfactory/ssh-agent@v0.9.0
        with:
          ssh-private-key: ${{ secrets.AWS_PEM_KEY }}

      - name: Setup SSH Agent for Target
        uses: webfactory/ssh-agent@v0.9.0
        with:
          ssh-private-key: ${{ secrets.AWS_PEM_KEY }}

      - name: Copy .env file and Deploy 1
        if: github.event.inputs.profile == 'prod'
        env:
          BASTION_HOST: ${{ secrets.BASTION_HOST }}
          TARGET_HOST: ${{ secrets[format('{0}_SSH_HOST_1', github.event.inputs.profile)] }}
          SSH_USER: ${{ secrets[format('{0}_SSH_USER', github.event.inputs.profile)] }}
          ECR_IMAGE_URI: ${{ secrets[format('{0}_ECR_REPOSITORY_URI', github.event.inputs.profile)] }}
          AWS_REGION: ${{ secrets.AWS_REGION }}
        run: |
          echo "Starting SSH tunnel to $TARGET_HOST via $BASTION_HOST..."
          ssh -o StrictHostKeyChecking=no -N -L 2222:$TARGET_HOST:22 $SSH_USER@$BASTION_HOST &
          TUNNEL_PID=$!
          sleep 5  # SSH 터널 안정화 대기

          echo "Copying .env file to target host through SSH tunnel..."
          scp -P 2222 -o StrictHostKeyChecking=no .env $SSH_USER@localhost:~/.env || exit 1

          echo "Deploying Docker container on target host through SSH tunnel..."
          ssh -p 2222 -o StrictHostKeyChecking=no $SSH_USER@localhost << EOF
            set -e
            aws ecr get-login-password --region $AWS_REGION | sudo docker login --username AWS --password-stdin $ECR_IMAGE_URI
            sudo docker pull $ECR_IMAGE_URI:latest
            sudo docker stop ssc-backend || true
            sudo docker rm ssc-backend || true
            sudo docker run -d --name ssc-backend -p 8080:8080 \
              --env-file ~/.env \
              $ECR_IMAGE_URI:latest
            sudo docker image prune -a -f
          EOF

          kill $TUNNEL_PID
          echo "Deployment to production via Bastion complete."

      - name: Copy .env file and Deploy 2
        if: github.event.inputs.profile == 'prod'
        env:
          BASTION_HOST: ${{ secrets.BASTION_HOST }}
          TARGET_HOST: ${{ secrets[format('{0}_SSH_HOST_2', github.event.inputs.profile)] }}
          SSH_USER: ${{ secrets[format('{0}_SSH_USER', github.event.inputs.profile)] }}
          ECR_IMAGE_URI: ${{ secrets[format('{0}_ECR_REPOSITORY_URI', github.event.inputs.profile)] }}
          AWS_REGION: ${{ secrets.AWS_REGION }}
        run: |
          echo "Starting SSH tunnel to $TARGET_HOST via $BASTION_HOST..."
          ssh -o StrictHostKeyChecking=no -N -L 2222:$TARGET_HOST:22 $SSH_USER@$BASTION_HOST &
          TUNNEL_PID=$!
          sleep 5  # SSH 터널 안정화 대기

          echo "Copying .env file to target host through SSH tunnel..."
          scp -P 2222 -o StrictHostKeyChecking=no .env $SSH_USER@localhost:~/.env || exit 1

          echo "Deploying Docker container on target host through SSH tunnel..."
          ssh -p 2222 -o StrictHostKeyChecking=no $SSH_USER@localhost << EOF
            set -e
            aws ecr get-login-password --region $AWS_REGION | sudo docker login --username AWS --password-stdin $ECR_IMAGE_URI
            sudo docker pull $ECR_IMAGE_URI:latest
            sudo docker stop ssc-backend || true
            sudo docker rm ssc-backend || true
            sudo docker run -d --name ssc-backend -p 8080:8080 \
              --env-file ~/.env \
              $ECR_IMAGE_URI:latest
            sudo docker image prune -a -f
          EOF

          kill $TUNNEL_PID
          echo "Deployment to production via Bastion complete."

      - name: Direct Deploy to EC2 (for Development)
        if: github.event.inputs.profile != 'prod'
        env:
          SSH_HOST: ${{ secrets[format('{0}_SSH_HOST', github.event.inputs.profile)] }}
          SSH_USER: ${{ secrets[format('{0}_SSH_USER', github.event.inputs.profile)] }}
          ECR_IMAGE_URI: ${{ secrets[format('{0}_ECR_REPOSITORY_URI', github.event.inputs.profile)] }}
          AWS_REGION: ${{ secrets.AWS_REGION }}
        run: |
          echo "Copying .env file to target EC2 instance for development..."
          scp -o StrictHostKeyChecking=no .env $SSH_USER@$SSH_HOST:~/.env

          echo "Starting deployment on development EC2 instance..."
          ssh -o StrictHostKeyChecking=no $SSH_USER@$SSH_HOST << EOF
            set -e
            aws ecr get-login-password --region $AWS_REGION | sudo docker login --username AWS --password-stdin $ECR_IMAGE_URI
            sudo docker pull $ECR_IMAGE_URI:latest
            sudo docker stop ssc-backend || true
            sudo docker rm ssc-backend || true
            sudo docker run -d --name ssc-backend -p 8080:8080 --env-file ~/.env $ECR_IMAGE_URI:latest
            sudo docker image prune -a -f
          EOF

          echo "Development deployment complete."
```

#### Github actions 환경에 JDK, Gradle 필요

- React app
    - 빌드에 필요한 도구(Node.js, npm)이 Github Actions 기본 환경에 포함되어있음
- Spring boot app
    - Github Actions 기본 환경에 포함 X
        - JDK 설치 필요, JAR 파일 생성해 이를 Docker 이미지로 만듬
    - 멀티 모듈 프로젝트
        - Gradle 빌드 필요

#### ssh agent

- run: 에서 SSH 관련 명령이 사용될 때 Github Actions 머신이 ssh-agent에 설정된 SSH 키를 자동으로 참조하게 됨
    - [usage](https://github.com/webfactory/ssh-agent)

#### .env 파일 구성

- 컨테이너 환경변수를 파일로 지정
- [usage](https://docs.docker.com/reference/cli/docker/container/run/#env)
- 아래와 같이 `<variable>=value` 문법

```properties
SPRING_PROFILES_ACTIVE=prod
MONGODB_URI=mongodb://username:password@host:port/dbname
JWT_SECRET_KEY=mysecretkey
SERVER_PORT=8080
CORS_ALLOWED_ORIGINS=mydomain
SPRING_LOG_LEVEL=INFO
WEB_LOG_LEVEL=DEBUG
SECURITY_LOG_LEVEL=DEBUG
APP_LOG_LEVEL=DEBUG
```

- SPRING_PROFILES_ACTIVE
    - Spring profile 결정하는 환경변수
    - 이 값에 따라 application-{profile}.properties 파일을 로드하게 됨
    - [usage](https://spring.io/guides/gs/spring-boot-docker)
- 나머지 환경변수는 application.properties의 값으로 사용됨

### application-prod.properties 작성

- 컨테이너의 환경변수를 사용하게 됨

```properties
### MongoDB
alpha.mongodb.uri=${MONGODB_URI}
alpha.mongodb.connectionPool.size=10
alpha.mongodb.connection.timeoutMs=10000
### Server port
server.port=${SERVER_PORT:8080}
### Cors
cors.allowed-origins=${CORS_ALLOWED_ORIGINS}
### JWT secretKey
alpha.jwt.secret=${JWT_SECRET_KEY}
### Logging
logging.level.org.springframework=${SPRING_LOG_LEVEL:INFO}
logging.level.org.springframework.web=${WEB_LOG_LEVEL:DEBUG}
logging.level.org.springframework.security=${SECURITY_LOG_LEVEL:DEBUG}
logging.level.com.g2s.alpha=${APP_LOG_LEVEL:DEBUG}
```