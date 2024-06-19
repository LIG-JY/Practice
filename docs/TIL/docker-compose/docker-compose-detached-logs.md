# 도커 컴포즈 detached 모드로 실행 시 실시간 로그 확인 방법

## content

도커 컴포즈로 서비스를 실행할 때 `-d` 옵션을 사용하면 백그라운드에서 실행되어 로그를 확인하기 어렵습니다. 이때는 `docker-compose logs` 명령어로 로그를 확인할 수 있습니다.

여기서 -f 옵션 추가하면 실시간으로 로그를 확인할 수 있습니다.

```shell
docker-compose logs -f
```

## reference

https://docs.docker.com/reference/cli/docker/compose/logs/
