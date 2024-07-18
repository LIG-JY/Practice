# workflow script

## github action workflow 스크립트 작성할 때 팁

github repository의 `Actions secrets and variables`는 웹에서 추가할 때 변수명을 대문자로 작성한다.

workflow 스크립트를 작성할 때는 대소문자 구분 없이 변수명를 사용할 수 있다.

따라서 github cli에서 -f 옵션을 통해 변수를 입력할 때 소문자를 입력해도 괜찮다. 예를 들어 아래와 같이 입력한다면

```shell
gh workflows run deploy.yml -f profile=dev
```

스크립트에서 dev_ssh_host 변수는 `Actions secrets and variables`의 DEV_SSH_HOST와 대응하게 된다.

```yml
SSH_HOST: ${{ secrets[format('{0}_ssh_host', github.event.inputs.profile)] }}
```
