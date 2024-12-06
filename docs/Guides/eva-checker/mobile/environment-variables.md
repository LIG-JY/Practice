# React Native + Expo Environment Variable

## .env

> The Expo CLI will automatically load environment variables with an EXPO_PUBLIC_ prefix from .env files for use within
> your JavaScript code whenever you use the Expo CLI, such as when running npx expo start to start your app in local
> development mode.

- .env 파일에서 `EXPO_PUBLIC_[NAME]=VALUE` 형태로 EXPO_PUBLIC_ 접미사 붙여야 Expo Cli 에서 로드할 수 있음
- expo 실행 환경에서 `process.env.<환경변수>` 를 대체함
    - [문서](#환경-변수-총정리-문서) 예시 참고

## eas.json

- EAS Build 사용 시 추가적으로 환경 변수 설정 방법

> Because EAS Build and Workflows jobs run on a remote server, .env files may not be available. Additionally, you may
> want to use environment variables outside of your project code to customize your app binary at build time, like
> setting
> a bundle identifier or a private key for an error reporting service.

- .env는 로컬에서 사용하고, eas.json 으로 설정하는 방법은 remote에서 사용하는 것을 권함
- -EAS 서버에 환경 변수를 저장하고, 이를 로컬에 동기화하는 방법

> After creating an environment variable, you can read it on subsequent EAS Build jobs with process.env.VARIABLE_NAME
> from Node.js or in shell scripts as $VARIABLE_NAME.

- 코드에서 접근 방법은 동일함 `process.env.<환경변수>`

- [실용적인 사례](https://docs.expo.dev/eas/using-environment-variables/)
- https://docs.expo.dev/build/eas-json/#environment-variables
- https://docs.expo.dev/eas/environment-variables/

## EAS Secret

- ?
- 설명을 못 찾겠음...

```shell
eas secret:create --name SECRET_KEY --value "your-secret-value"
```

## 환경 변수 총정리 문서

- https://docs.expo.dev/guides/environment-variables/