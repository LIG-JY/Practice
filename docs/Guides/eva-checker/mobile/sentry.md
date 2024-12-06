# Sentry

- https://docs.sentry.io/platforms/react-native/manual-setup/expo/

1. 설치

```shell
npx expo install @sentry/react-native
```

2. 진입점에 코드 추가

- 이 프로젝트의 경우 App.tsx

- dsn:
    - [docs](https://docs.sentry.io/concepts/key-terms/dsn-explainer/)
    - Sentry 프로젝트에 대한 접근 정보를 포함함
    - 앱이 Sentry에 에러 데이터를 전송하기 위해 사용하는 URL
        - 앱의 오류 데이터를 Sentry 서버로 보내는데 사용함

3. Sentry Expo Plugin 추가

- Bundles:
    - 앱의 코드가 압축되고 번들링된 형태로, React Native 또는 Expo 앱에서 실제 실행되는 코드
    - 코드는 난독화(Obfuscation)됨

- Source Maps:
    - 번들과 실제 코드를 매핑하는 파일
    - 에러가 발생했을 때, 압축된 코드에서의 에러를 원본 코드(개발자가 작성한 코드)로 매핑해주는 역할
    - Expo Plugin 사용하면 애플리케이션 빌드 과정에서 자동으로 Sentry 서버로 업로드
        - 이 때 인증을 위해 SENTRY_AUTH_TOKEN 필요

4. 환경변수 설정

- Expo CLI를 통해 환경변수 설정
    - [docs](https://docs.expo.dev/guides/environment-variables/)
    - 또는 expo 웹페이지에서 project/configuration/Environment-variables >> 여기서 등록 및 수정 가능

```shell
eas secret:create --name SENTRY_DSN --value "<your-dsn>"
eas secret:create --name SENTRY_AUTH_TOKEN --value "<your-auth-token>"
```


- SENTRY_DSN 환경변수는 App.tsx 에서 sentry 환경설정 할 때 사용됨

- SENTRY_AUTH_TOKEN 생성은 [여기](https://docs.sentry.io/platforms/react-native/manual-setup/expo/) 링크에서
- SENTRY_AUTH_TOKEN 환경변수는 app.config.js 파일에서 plugin 필드에서 사용됨
    - app.config.js 는 EXPO 런타임 제어에 사용!
    - process.env는 런타임에서 제한적임

```javascript
{
    "expo": {
        "plugins": [
            [
                "@sentry/react-native/expo",
                // Sentry Expo Plugin 추가
                {
                    url: "https://sentry.io/",
                    organization: "g2s",
                    // Sentry의 organization 이름
                    project: "EVA-Checker",
                    // Sentry의 project 이름
                    authToken: process.env.SENTRY_AUTH_TOKEN // 환경 변수로 인증 토큰 제공
                }
            ]
        ]
    }
}
```

```shell
eas secret:list
```

- 환경변수 확인 가능
    - expo project 별로 환경변수 설정


5. Sentry Metro Plugin 추가

- [Metro Bundler](https://metrobundler.dev/)(React Native에서 기본적으로 사용하는 번들러)와 통합
    - Source Map에 고유한 Debug Id 추가
    - 번들링 과정에서 생성된 Source Map을 Sentry 친화적인 형식으로 설정

- 프로젝트 루트 디렉토리에 파일 추가
    - metro.config.js

```js
// const { getDefaultConfig } = require("expo/metro-config");
const {getSentryExpoConfig} = require("@sentry/react-native/metro");

// const config = getDefaultConfig(__dirname);
const config = getSentryExpoConfig(__dirname);

module.exports = config;
```

6. 개발/프로덕션 환경 분리

- 전체 흐름은 아래와 같음
    - eas.json 파일에 프로필에 따라 환경변수 "ENV" 필드를 정의
    - 이 값을 빌드 시점에 app.config.js 파일에서 환경변수를 읽어 extra 필드에 값을 저장
    - 이 값은 실행 중 `Constants.expoConfig.extra` 코드로 접근할 수 있음

- [문서](https://docs.expo.dev/versions/latest/config/app/#extra)를
  참고하면 [Expo Constants API](https://docs.expo.dev/versions/latest/sdk/constants/#constantsmanifest) 사용을 권함
    - `__DEV__` 와 같은 플래그 사용해 코드에서 환경을 구분하는 방법도 있음

> Any extra fields you want to pass to your experience. Values are accessible via `Constants.expoConfig.extra`

- eas.json 파일에서 환경에 따라 환경 변수 설정
- 빌드 시점에 환경 변수를 등록함
    - `process.env.ENV` 로 사용할 수 있음

```json
{
  "build": {
    "production": {
      "env": {
        "ENV": "production",
        "API_URL": "https://api.example.com"
      }
    },
    "development": {
      "env": {
        "ENV": "development",
        "API_URL": "http://localhost:3000"
      }
    }
  }
}
```

- app.config.js에서 extra.ENV 상수로 등록:
    - [app.config.js](https://docs.expo.dev/versions/latest/config/app/#extra)
    - [Expo constant](https://docs.expo.dev/versions/latest/sdk/constants/#constantsmanifest)

```javascript
import 'dotenv/config';

export default ({config}) => ({
    ...config,
    name: "MyApp",
    slug: "my-app",
    version: "1.0.0",
    extra: {
        ENV: process.env.ENV || "development",
    },
});
```

- 이렇게 extra 필드로 등록하면 코드에서 아래와 같이 사용 가능

```ts
import Constants from "expo-constants";

const ENV = Constants.expoConfig.extra["ENV"]; // 현재 ENV 가져오기

console.log(`Running in ${ENV} environment`);
```

- [Eas-build environment-variables](https://docs.expo.dev/build/eas-json/#environment-variables)

7. 분기처리하는 공통 로깅함수 정의

```typescript
import * as Sentry from "@sentry/react-native";
import Constants from "expo-constants";

const env: string | undefined = Constants.expoConfig?.extra?.["ENV"];

export const logMessage = (message: string) => {
    if (env === "production") {
        Sentry.captureMessage(message); // Sentry에 메시지 전송
    } else {
        console.log(`[LOG]: ${message}`); // 개발 환경에서는 콘솔 출력
    }
};

export const logError = (error: Error) => {
    if (env === "production") {
        Sentry.captureException(error); // Sentry에 에러 전송
    } else {
        console.error(`[ERROR]:`, error); // 개발 환경에서는 콘솔 출력
    }
};
```

- `Sentry.captureException(error);`
- 이거 사용하래요