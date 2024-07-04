# 명령줄에서 코틀린 컴파일하고 실행하기

## 코틀린 런타임 포함시키기

### [바이트 코드만 생성하기]

```shell
kotlinc-jvm hello.kt
```

- "HelloKt.class"
    - 클래스 파일 네이밍 규칙에 따라 바이트 코드 생성
        - 파일명에서 첫글자 대문자 변경, 파일의 이름 끝부분에 Kt 붙임

### [코틀린 런타임을 포함한 jar 파일 생성]

```shell
kotlinc-jvm hello.kt -include-runtime -d hello.jar
```

- 코틀린 런타임을 포함해서 생성한 jar 파일
- classpath에 코틀린 런타임이 없어도 실행 가능
    - java -jar hello.jr

- 코틀린으로 작성된 코드를 자바 바이트코드로 컴파일하면, 코틀린 표준 라이브러리의 클래스 및 함수들을 사용하게 됨
- 기본적으로 코틀린 표준 라이브러리는 자바 표준 라이브러리에는 포함되지 않음
- 코틀린 표준 라이브러리의 클래스 및 함사를 실행하기 위해서는 코틀린 런타임이 필요함
- "-include-runtime" 플래그를 사용하면, 코틀린 런타임 라이브러리를 생성된 JAR 파일에 포함시켜 줌
    - 따라서 별도로 코틀린 런타임을 classpath에 추가하지 않아도 바로 실행할 수 있음

### reference

https://stackoverflow.com/questions/30565036/why-kotlin-needs-to-bundle-its-runtime-after-compiled


