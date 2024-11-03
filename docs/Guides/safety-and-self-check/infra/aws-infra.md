# AWS INFRA

## IAM Role EC2에 부여하기

- 역할 생성
- 신뢰할 수 있는 엔터티 선택
    - 신뢰할 수 있는 엔터티 유형:
        - AWS 서비스
        - EC2
    - 권한추가:
        - AmazonEC2ContainerRegistryFullAccess

- 배포할 EC2에 역할 추가
    - EC2 콘솔
        - 작업
        - 보안
        - IAM 역할 수정

- 역할을 부여해도 ecr에서 도커이미지를 다운 받는데 credential issue 발생하면 그냥 직접 로그인하는 명령어를 github action workflow 포함하기

## IAM 사용자

- 배포할 때 AWS credentials를 구성해야하기 때문에 생성

- 사용자 이름:
    - admin
- AWS Management Console에 대한 사용자 액세스 권한 제공 – 선택 사항:
    - 미선택
    - IAM 계정으로 브라우저에서 AWS Management Console에 접속할 일 없음
    - 루트계정만 AWS Management Console 이용
    - 이 IAM 계정은 프로그래밍 방식, CLI에서만 사용

- 권한설정:
    - AmazonEC2ContainerRegistryFullAccess
    - ECR 관련 작업만 수행함

- 액세스 키 생성
    - ECR에 푸시,풀 하려면 필요함
    - Github Repository에서 secret으로 관리

## ECR Container Hub

- 리포토리 이름:
    - safety-and-self-check-frontend/prod
    - safety-and-self-check-<역할>/<프로필>
- 이미지 태그 변경 가능성:
    - Mutable
        - CI/CD로 최신 빌드 이미지를 배포하는 경우라면 Mutable이 편리
        - 이미지 버전별 관리하려면 Immutable도 고려
- 암호화 구성:
    - AES-256
        - AWS KMS는 비용도 들고, 굳이?

- 리전:
    - ap-northeast-2

## 네트워크

### VPC

- VPC name tag:
    - safety-and-self-check-prod-vpc

- IPv4 CIDR 블록:
    - 10.0.0.0/16
    - VPC 내부 사설 IP 범위

- IPv6 CIDR 블록:
    - 없음

- 테넌시:
    - 기본값

### subnet, AZ 설정

- 가용 용역 수:
    - 2
    - 로드 밸런서 붙이려면 최소 2개

- 퍼블릭 서브넷 수:
    - 2

- 프라이빗 서브넷 수:
    - 2

- ap-northeast-2a 퍼블릭 서브넷 CIDR 블록:
    - 10.0.0.0/20
- ap-northeast-2C 퍼블릭 서브넷 CIDR 블록:
    - 10.0.16.0/20
- ap-northeast-2a 프라이빗 서브넷 CIDR 블록:
    - 10.0.128.0/20
- ap-northeast-2C 프라이빗 서브넷 CIDR 블록:
    - 10.0.64.0/20

- 이름 규칙:
    - safety-and-self-check-prod + 자원
    - safety-and-self-check-prod-subnet-public

- DNS 옵션:
    - DNS 호스트 이름 활성화
        - EC2 인스턴스가 퍼블릭 IP를 가질 경우, 퍼블릭 DNS 호스트 이름이 자동으로 할당
        - IP 대신, 호스트 이름으로 접근할 수 있으니, 편의를 위해 사용
    - DNS 확인 활성화
        - 위 옵션 활성화 했기 때문에 VPC내에서 DNS 쿼리 가능하도록 활성화
        - VPC 내부 리소스들이 AWS의 DNS 서버를 통해 DNS 확인 요청 처리함

### NAT 게이트 웨이

- 없음
    - 비용 절감

### VPC 엔드포인트

- 없음

### 인터넷 게이트웨이

- 생성

### 라우팅 테이블

- 퍼블릭 용도 라우팅 테이블
    - 이름: safety-and-self-check-prod-rt-public
    - 0.0.0.0/0 대상: igw
    - 10.0.0.0/16 대상: local
        - VPC의 CIDR과 동일

- 프라이빗 용도 라우팅 테이블
    - 이름: safety-and-self-check-prod-rt-private
    - 10.0.0.0/16 대상: local
        - VPC의 CIDR과 동일

- 기본 라우팅 테이블
    - 이름: safety-and-self-check-prod-rt-default
    - 자동 생성
    - 사용 안 됨

### 보안 그룹

- default:
    - 인바운드 규칙
        - vpc local에서 모두 허용(10.0.0.0/16)
    - 아웃바운드 규칙
        - 모든 트래픽 허용

- 프론트 서버용
    - 인바운드 규칙
        - 점프 서버용 보안 그룹에서 SSH 허용
        - 로드 밸런서용 보안 그룹에서 모든 트래픽 허용
    - 아웃바운드 규칙
        - 모든 트래픽 허용

- 웹 서버용
    - 인바운드 규칙
        - 점프 서버용 보안 그룹에서 SSH 허용
        - 로드 밸런서용 보안 그룹에서 모든 트래픽 허용
    - 아웃바운드 규칙
        - 모든 트래픽 허용

- 점프 서버용 보안 그룹
    - 인바운드 규칙
        - 유형: SSH
        - 소스: 0.0.0.0/0

- 로드 밸런서용 보안 그룹
    - 인바운드 규칙
        - 유형 HTTPS
        - 소스: 0.0.0./0
    - 아웃바운드 규칙
        - 모든 트래픽 허용
        - 대상: 프라이빗 서브넷의 CIDR 블록

- DB용 보안 그룹
    - 인바운드 규칙
        - 웹 서버용 보안 그룹으로 부터 모든 트래픽 허용
    - 아웃바운드 규칙
        - 모든 트래픽 허용

## 점프 서버

### ec2 spec

- Amazon Machine Image:  
  -Ubuntu Server 24.04 LTS(HVM), SSD Volume Type

- 아키텍쳐:
    - 64비트(x86)

- 인스턴스 유형:
    - t2.micro

- 서브넷:
    - 위에서 생상한 VPC의 public

- 퍼블릭 IP 자동 할당:
    - 활성화

- 보안그룹:
    - safety-and-self-check-prod-sg-bastion

## 웹 서버

### ec2 spec

- Amazon Machine Image:  
  -Ubuntu Server 22.04 LTS(HVM), SSD Volume Type
    - mongo shell 이 24.04 지원 안 함

- 아키텍쳐:
    - 64비트(x86)

- 인스턴스 유형:
    - t2.micro

- 서브넷:
    - 위에서 생상한 VPC의 public
    - 보안 그룹에서 인바운드 규칙 제한
    - 인터넷 게이트웨이로 외부 api 서비스 호출 필요함
        - 주소 검색

- 퍼블릭 IP 자동 할당:
    - 활성화
    - 로드밸런서부터 요청만 받음
        - 보안그룹으로 제한

- 보안그룹:
    - safety-and-self-check-prod-sg-web

- 이름:
    - safety-and-self-check-prod-ec2-web01 / -web02
    - 2개임

## 프론트 서버

### ec2 spec

- Amazon Machine Image:  
  -Ubuntu Server 22.04 LTS(HVM), SSD Volume Type
    - 백엔드 ec2랑 스펙 동일

- 아키텍쳐:
    - 64비트(x86)

- 인스턴스 유형:
    - t2.micro

- 서브넷:
    - 위에서 생상한 VPC의 public01

- 퍼블릭 IP 자동 할당:
    - 활성화
    - 인터넷 게이트웨이로 소프트웨어 업데이트, 외부 리소스 접근 가능

- 보안그룹:
    - safety-and-self-check-prod-sg-frontend
        - 백엔드 ec2 보안 그룹이랑 동일
    - 인바운드
        - 로드밸런서부터 요청만 받음
        - 보안그룹으로 제한
    - 아웃바운드
        - 인터넷 게이트웨이로 소프트웨어 업데이트, 외부 리소스 접근 가능

- 이름:
    - safety-and-self-check-prod-ec2-frontend

## 로드 밸런서

- VPC
    - 웹 서버, 점프 서버가 생성된 VPC

- 가용역역
    - 위 VPC에 포함된 퍼블릭 서브넷

- 보안그룹
    - 위의 default 보안 그룹
        - vpc local에서 모든 인바운드 트래픽 허용
    - 위의 로드밸런서용 보안 그룹
        - 외부에서 http, https 인바운드 트래픽 허용(리스너)

- 리스너
    - 80 포트
        - 테스트 용
    - 443
        - https 프로덕션 요청용

- 대상그룹
    - 이름:
        - safety-and-self-check-prod-tg
    - 프로토콜: HTTP
    - 포트: 8080
    - 대상: 위의 웹서버 2개

- 헬스체크 경로
    - `/health`

### 로드벨런서 작동 확인

- 간단한 서빙 문서

```html
// index.html
<html>
<body>self-and-self-chek</body>
</html>
```

```text
// health
ok
```

- HTTP 서버는 기본적으로 파일 이름과 경로를 기반으로 요청을 처리
    - `health 라는 파일 만들어서 서빙

```shell
python3 -m http.server 8080
```

- 서버를 띄우면 로드밸런서에서 /health 경로로 헬스체크 요청이 들어오는 것 확인 가능

```shell
Serving HTTP on 0.0.0.0 port 8080 (http://0.0.0.0:8080/) ...
10.0.30.45 - - [24/Oct/2024 09:23:01] "GET /health HTTP/1.1" 200 -
10.0.14.3 - - [24/Oct/2024 09:23:14] "GET /health HTTP/1.1" 200 -
```

- 대상 그룹 aws 콘솔에서 상태 확인하고 모든 인스턴스 healthy 확인 후
- 로드밸런서 dns로 http 요청 보내서 200 응답 확인하기

## 도메인 취득

- Route 53 도메인 취득
- 이메일 인증

## SSL 인증서 생성

- AWS Certificate Manager 사용
- 요청하기
    - 퍼블릭 인증서 요청
    - 도메인 이름:
        - Route 53으로 취득한 도메인 입력
    - 검증 방법:
        - DNS 검증
    - 키 알고리즘:
        - RSA 2048
- 추가작업
    - Amazon Route 53에서 DNS 레코드 생성
        - AWS가 인증서를 요청한 사용자가 해당 도메인에 소유권 또는 관리 권한이 있는지 확인하는 절차가 필요
        - CNAME 레코드는 한 도메인이 다른 도메인을 참조하는 DNS record
        - AWS에서 제공한 고유한 CNAME 레코드를 도메인에 추가하면, AWS는 도메인에서 이 레코드가 설정된 것을 확인하고 해당 도메인을 소유하고 있다고 검증

## 로드밸런서 HTTPS 요청 처리하도록 설정

- 리스너 추가
    - 프로토콜:
        - HTTPS
    - OpenID 또는 Amazon Cognito 사용 X
        - 자체적으로 로그인 처리
    - 대상 그룹:
        - 대상 그룹 이름:
            - safety-and-self-check-prod-front
        - 프로토콜/포트:
            - HTTP/80
            - 프론트 서버 nginx 80 리스닝
        - VPC:
            - 위에서 만든 VPC
        - 헬스체크 경로:
            - /
    - 대상 그룹 고정성(sticky session):
        - X
    - 보안 리스너 설정:
        - 보안 정책:
            - 보안 카테고리:
                - 모든 카테고리
            - 정책 이름:
                - 권장 적힌거
        - 기본 SSL/TLS 서버 인증서:
            - ACM에서 등록한 도메인에 해당하는 인증서 가져오기
        - 클라이언트 인증서 처리:
            - X

## 취득한 도메인에 레코드 추가

- 트래픽을 로드밸런서로 라우팅
- 레코드 생성
    - 레코드 이름:
        - 루트 도메인에 대한 레코드를 생성
    - 레코드 유형:
        - A
    - 별칭(Alias):
        - on
        - 트래픽 라우팅 대상:
            - 로드밸런스에 대한 별칭
            - 리전 ap-northeast-2
            - 위에서 생성한 로드 밸런서
            - 라우팅 정책: 단순 (기본 트래픽 전달)
            - 대상 상태 평가: 예 (대상이 정상일 때만 트래픽 전달)

## 로드밸런서에 backend 리스너 규칙 추가

- 기존에 추가한 리스너에 규칙 추가
  - /api/* 로 시작하는 요청은 backend 대상 그룹으로 라우팅
  
- 규칙 추가:
  - 이름:
    - api
- 규칙 조건 정의:
  - 조건 추가:
    - 경로:
      - /api/*
      - wild card 필수
- 규칙 작업 정의:
  - OpenID 또는 Amazon Cognito 사용:
    - X
  - 라우팅 액션:
    - 대상 그룹으로 전달
    - 대상 그룹:
      - backend tg
    - 대상 그룹 고정성:
      - X
- 규칙 우선 순위 설정:
  - 지금 생성한 경로 규칙이 우선순위가 높게 설정
  - /api 경로는 백엔드 대상 그룹으로 라우팅, 나머지 요청은 프론트 대상 그룹으로 라우팅

## ssh config 스크립트

```shell
# ~/.ssh/config
Host bastion
    Hostname <점프 서버의 퍼블릭 IP> 
    User ubuntu                # ubuntu 일반적으로 'ubuntu'
    IdentityFile <SSH 키 파일 절대 경로> 

Host web01
    Hostname <웹 서버 프라이빗 IP> 
    User ubuntu                 # ubuntu 일반적으로 'ubuntu'
    IdentityFile <동일한 SSH 키 파일 절대 경로>
    ProxyCommand ssh bastion -W %h:%p  # bastion을 경유하여 웹 서버에 접속
    
Host web02
    Hostname <웹 서버 프라이빗 IP> 
    User ubuntu                 # ubuntu 일반적으로 'ubuntu'
    IdentityFile <동일한 SSH 키 파일 절대 경로>
    ProxyCommand ssh bastion -W %h:%p  # bastion을 경유하여 웹 서버에 접속

Host frontend
    Hostname <프론트 서버 프라이빗 IP> 
    User ubuntu                 # ubuntu 일반적으로 'ubuntu'
    IdentityFile <동일한 SSH 키 파일 절대 경로>
    ProxyCommand ssh bastion -W %h:%p  # bastion을 경유하여 웹 서버에 접속
```

아래 명령어로 접속할 수 있음

```shell
ssh <HostName>
```

예를들어 웹 서버 접속

```shell
ssh web01
```