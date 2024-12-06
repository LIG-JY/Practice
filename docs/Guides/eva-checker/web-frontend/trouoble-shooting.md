# Trouble Shooting

## 컨테이너 종료 시 확인

1. container id 확인

```shell
sudo docker ps -a
```

2. 종료 코드 확인

```shell
docker inspect <container_id> --format='{{.State.ExitCode}}'
```

3. 로그 확인

```shell
docker logs <container_id>
```

### exit code 255

- 이거 나오면 이미지 실행시켜서 까봐야함
  - nginx 로그
  - ec2 메모리 확인

## 컨테이너 자동 재시작

```shell
sudo docker run -d --name <my_app_name> --restart on-failure -p 80:80 --env-file ~/.env <imange_name>
```

- [docs](https://docs.docker.com/reference/cli/docker/container/run/#restart)