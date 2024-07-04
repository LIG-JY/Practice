# docker-compose 명령어가 작동하는 기본 경로

## The Compose file

- Compose 파일의 defaujlt path는 working directory에 있는 compose.yaml(기본값) 또는 compose.yml
    - 따라서 Compose는 기본적으로 현재 작업 디렉터리에서 이러한 파일들을 검색함
    - 현재 작업 디렉토리에 docker-compose.yml이 없으면, docker-commpse 명령어가 정상적으로 작동하지 않음
- Compose는 이전 버전과의 하위 호환성을 위해 docker-compose.yaml 및 docker-compose.yml도 지원
    - 두 파일이 모두 존재하는 경우, 표준 compose.yaml을 선호함

## reference

https://docs.docker.com/compose/compose-application-model/