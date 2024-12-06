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

프로젝트 루트에 작성

```dockerfile
# Stage 1: Build the React app
FROM node:20 AS build

WORKDIR /app

# Install dependencies
COPY package*.json ./
RUN npm install

# Copy the rest of the application files
COPY . .

# Build the app
RUN npm run build

# Stage 2: Serve with Nginx
FROM nginx:alpine

# Copy built files from the previous stage
COPY --from=build /app/dist /usr/share/nginx/html

# Copy custom Nginx configuration
COPY nginx.conf /etc/nginx/nginx.conf

# Expose port 80
EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]
```

- vite 사용하면 node 18 또는 20 이상

- 컨테이너 내부 포트 80

### nginx config 작성

프로젝트 루트에 작성

```shell
worker_processes 1;

events {
    worker_connections 1024;
}

http {
    include /etc/nginx/mime.types;
    default_type application/octet-stream;

    server {
        listen 80;
        server_name _;

        # Root directory for serving the built files
        root /usr/share/nginx/html;
        index index.html;

        # Serve the index.html for any route
        location / {
            try_files $uri /index.html;
        }

        # Enable caching for static files
        location ~* \.(js|css|png|jpg|jpeg|gif|ico|svg)$ {
            expires 1y;
            add_header Cache-Control "public, max-age=31536000, immutable";
        }

        # Enable Gzip compression for better performance
        gzip on;
        gzip_types text/plain text/css application/javascript application/json image/svg+xml;
        gzip_min_length 256;
    }
}
```

- server_name:
    - `_`는 모든 도메인의 요청을 처리하는 와일드카드

- try_files:
    - $uri
        - 로드 밸런서에서 요청을 보내기 때문에 항상 root(/)로 결정
            - root에 파일(index.html)이 존재하면 반환
            - root에 파일이 존재하지 않으면 default로 /index.html 반환
            - 결론적으로 어떤 경로든 index.html 반환

- 컨테이너 내부 80포트로 요청 listen

### Github Action 스크립트 작성

root/.github/ 에 작성

```yaml
name: deploy-frontend

on:
  workflow_dispatch:
    inputs:
      profile:
        required: true
        type: string
        description: 'Deployment environment (e.g., prod, develop)'
      branch:
        required: true
        type: string
        description: 'Branch to Deploy'

jobs:
  build-and-deploy:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout Code
        uses: actions/checkout@v4
        with:
          ref: ${{ github.event.inputs.branch }}

      - name: Configure AWS Credentials
        uses: aws-actions/configure-aws-credentials@v3
        with:
          aws-access-key-id: ${{ secrets.AWS_ACCESS_KEY_ID }}
          aws-secret-access-key: ${{ secrets.AWS_SECRET_ACCESS_KEY }}
          aws-region: ${{ secrets.AWS_REGION }}

      - name: Login to Amazon ECR
        uses: aws-actions/amazon-ecr-login@v2

      - name: Build Docker Image
        run: |
          echo "Building Docker image..."
          docker build -t ssc-web-front .
          docker tag ssc-web-front:latest ${{ secrets[format('{0}_ECR_REPOSITORY_URI', github.event.inputs.profile)] }}:latest
          echo "Docker image tagged as ${{ secrets[format('{0}_ECR_REPOSITORY_URI', github.event.inputs.profile)] }}:latest"

      - name: Push Docker Image to Amazon ECR
        run: |
          echo "Pushing Docker image to Amazon ECR..."
          docker push ${{ secrets[format('{0}_ECR_REPOSITORY_URI', github.event.inputs.profile)] }}:latest
          echo "Docker image pushed successfully."

      - name: Create .env File
        run: |
          echo "Creating .env file..."
          echo "VITE_API_BASE_URL=${{ secrets[format('{0}_API_BASE_URL', github.event.inputs.profile)] }}" > .env
          if [ "${{ github.event.inputs.profile }}" == "prod" ]; then
            echo "NODE_ENV=production" >> .env
          else
            echo "NODE_ENV=development" >> .env
          fi
          echo ".env file created with VITE_API_BASE_URL and NODE_ENV settings."

      - name: Setup SSH Agent for Bastion
        uses: webfactory/ssh-agent@v0.9.0
        with:
          ssh-private-key: ${{ secrets.AWS_PEM_KEY }}

      - name: Setup SSH Agent for Target
        uses: webfactory/ssh-agent@v0.9.0
        with:
          ssh-private-key: ${{ secrets.AWS_PEM_KEY }}

      - name: Copy and Deploy to EC2 via Bastion (for Production)
        if: github.event.inputs.profile == 'prod'
        env:
          BASTION_HOST: ${{ secrets.BASTION_HOST }}
          TARGET_HOST: ${{ secrets[format('{0}_SSH_HOST', github.event.inputs.profile)] }}
          SSH_USER: ${{ secrets[format('{0}_SSH_USER', github.event.inputs.profile)] }}
          ECR_IMAGE_URI: ${{ secrets[format('{0}_ECR_REPOSITORY_URI', github.event.inputs.profile)] }}
          AWS_REGION: ${{ secrets.AWS_REGION }}
        run: |
          echo "Starting SSH tunnel to $TARGET_HOST via $BASTION_HOST..."
          ssh -o StrictHostKeyChecking=no -N -L 2222:$TARGET_HOST:22 $SSH_USER@$BASTION_HOST &
          TUNNEL_PID=$!
          sleep 5  # SSH 터널 안정화 대기

          echo "Attempting to copy .env file to target host through tunnel..."
          scp -P 2222 -o StrictHostKeyChecking=no .env $SSH_USER@localhost:~/.env || exit 1

          echo "Deploying Docker container on target host..."
          ssh -p 2222 -o StrictHostKeyChecking=no $SSH_USER@localhost << EOF
            aws ecr get-login-password --region $AWS_REGION | sudo docker login --username AWS --password-stdin $ECR_IMAGE_URI
            sudo docker pull $ECR_IMAGE_URI:latest
            sudo docker stop $ECR_IMAGE_URI:latest || true
            sudo docker rm $ECR_IMAGE_URI:latest || true
            sudo docker run -d --name $ECR_IMAGE_URI:latest -p 80:80 --env-file ~/.env $ECR_IMAGE_URI:latest
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
          echo "Copying .env file to target EC2 instance..."
          scp -o StrictHostKeyChecking=no .env $SSH_USER@$SSH_HOST:~/.env

          echo "Starting deployment on target host $SSH_HOST..."
          ssh -o StrictHostKeyChecking=no $SSH_USER@$SSH_HOST << EOF
            set -e
            aws ecr get-login-password --region $AWS_REGION | sudo docker login --username AWS --password-stdin $ECR_IMAGE_URI
            sudo docker pull $ECR_IMAGE_URI:latest
            sudo docker stop $ECR_IMAGE_URI:latest || true
            sudo docker rm $ECR_IMAGE_URI:latest || true
            sudo docker run -d --name $ECR_IMAGE_URI:latest -p 80:80 --env-file ~/.env $ECR_IMAGE_URI:latest
            sudo docker image prune -a -f
          EOF

          echo "Development deployment complete."
```

- set up node.js:
    - [usage](https://github.com/actions/setup-node)

- Amazone ECR:
    - [usage](https://github.com/aws-actions/amazon-ecr-login)

- SSH Agent:
    - [usage](https://github.com/webfactory/ssh-agent)

- github.event.inputs.profile 값을 formatting 해서 github action secret과 mapping 할 때 대소문자 관계없이 대문자로
    - ex) prod 입력 >> PROD_ECR_REPOSITORY_URI

- .env
    - Vite 환경 변수는 빌드 시점에 주입됨
    - DockerFile 확인하면 'RUN npm run build' 실행할 때 주입됨

## TroubleShooting

### 호스트 EC2 ecr pull 권한 문제

```shell
Error response from daemon: Head <ECR_REPOSITORY_URI>: no basic auth credentials
```

- 해결방법
    - aws iam 로그인
        ```shell
         aws ecr get-login-password --region $AWS_REGION | sudo docker login --username AWS --password-stdin $ECR_IMAGE_URI
        ```
    - EC2에 IAM ROLE로 ECR 권한 부여

### 호스트 EC2에서 도커 컨테이너 로그 확인

ec2 접속 후 디버깅 용

```shell
sudo docker logs <image name>
```

- https://docs.docker.com/reference/cli/docker/container/ls/
