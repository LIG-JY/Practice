# 개발환경

## Vite로 React 프로젝트 생성

```shell
npm create vite@latest
```

- Select a framework:
    - React
- Select a variant:
    - TypeScript + SWC

[SWC](https://swc.rs/)

## 환경변수 설정

프로젝트 루트에 .env 파일을 생성

API Base URL 등록

```text
VITE_API_BASE_URL=http://localhost:8080
```

```typescript jsx
const API_BASE_URL = import.meta.env.VITE_API_BASE_URL;

axios.get(`${API_BASE_URL}/api/endpoint`)
```

## 개발 서버 실행

```shell
npm run dev
```

-
- 점검기간/동/호수 별 FILTER 기능
- 화면에 보이는 정보: 세부 항목별 점검 여부

## 주소찾기

- [npm](https://www.npmjs.com/package/@actbase/react-daum-postcode)

```shell
 Could not resolve "tslib"

    node_modules/@actbase/react-daum-postcode/lib/app.js:10:21:
      10 │ var _tslib = require("tslib");
         ╵                      ~~~~~~~

  You can mark the path "tslib" as external to exclude it from the bundle, which will remove this
  error and leave the unresolved path in the bundle. You can also surround this "require" call with
  a try/catch block to handle this failure at run-time instead of bundle-time.
```

위 오류 나오면 tslib 의존성 추가하기

```shell
npm install tslib
```

## styled components

```shell
npm install styled-components
```

## @types/node

- [npm link](https://www.npmjs.com/package/@types/node)

## react-select

- [npm link](https://www.npmjs.com/package/react-select)
