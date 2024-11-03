# 개발환경

## JWT secret key 생성

OpenSSl 활용

```shell
openssl rand -base64 64 | tr -d '\n'
```

출력 시 개행문자 제거