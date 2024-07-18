# docker-composes-script login

## docker login 명령어

non-TTY 환경에서 로그인 하기 위해서 --password-stdin flag를 사용해줘야함

```yml
echo \$DOCKERHUB_PASSWORD | sudo -E docker login --username \$DOCKERHUB_USERNAME --password-stdin
```

[도커 로그인](https://docs.docker.com/reference/cli/docker/login/)

## github cli로 work flow 실행하기

```shell
gh workflow run <github-action yaml file> --ref <branch name> -f <변수>=<값>
```

--ref : 어느 브랜치/태그/커밋에서 워크플로우 파일(.github/workflows 폴더 안의 yml)을 가져와 실행해야 하는가?


```shell
-f branch=example
```

변수로 branch를 지정하고 아래 check-out action에서 작업의 단계를 수행하기 위해 어느 버전(브랜치)의 코드를 체크아웃해야 하는가를 결정할 수 있다.

```yml
- name: check-out
  uses: actions/checkout@v4
  with:
    ref: ${{ github.event.inputs.branch }}

```

이렇게 입력하면 example 브랜치로 check out action을 하게 됨