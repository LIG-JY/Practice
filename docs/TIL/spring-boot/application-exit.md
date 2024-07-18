# application exit

- 모든 `SpringApplication`은 애플리케이션이 종료될 때 [`ApplicationContext`](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/ApplicationContext.html)가 정상적으로 종료(`graceful exit`)되도록 JVM에 종료 훅(`shutdown hook`)을 등록한다.

## [graceful exit](https://en.wikipedia.org/wiki/Graceful_exit)

- `graceful exit`은 프로그래밍 관용구 
- 프로그램이 비정상적인 상황을 감지했을 때 예측 가능한 방식(통제된 방식)으로 종료하는 것을 말함
- `graceful exit`은 오류를 감지하기 때문에 디버깅에 유리하다.
  - 오류를 감지하지 못해 이를 처리하지 않는 경우 엉뚱한 오류나 나중의 이상 행동이 발생할 수 있다. 이런 경우는 디버깅하기 더 어렵다. 
- `graceful exit`은 종료할 때 추가적인 단계를 수행할 수 있다. 따라서 프로그램을 재실행할 때 문제가 없도록 방지함
  - 리소스 관리
  - 데이터 손상 방지
- `graceful exit`이 항상 바람직한 것은 아니다.
  - 프로그램을 바로 crash하는 것이 코어 덤프나 스택 트레이스 같은 중요한 정보를 수집하여 디버깅에 유리할 수도 있음 
- 언어마다 구현이 다름
  - 예외를 지원하는 언어에서는 `graceful exit`가 예외 처리의 마지막 단계일 수 있음

## [shutdown hook](https://www.baeldung.com/jvm-shutdown-hooks)

- JVM이 종료되기 전에 실행할 함수를 등록할 수 있도록 하는 메커니즘이 있음
  - 이 때 등록되는 함수를 `shutdown hooks`라고 정의함
  - `shutdown hooks`는 리소스를 해제하거나 정리 작업을 할 때 유용함
- 'graceful exit'의 개념에 부분집합
  - 통제된 방식으로 `shutdown hooks`을 등록해 정상 종료를 할 수 있음
- `shutdown hooks`는 아래와 같이 동작
  - `shutdown hooks`는 초기화되고, 시작되지 않은 스레드로 구현
  - JVM이 종료 프로세스를 시작할 때, 등록된 모든 `shutdown hooks`를 시작
  - `shutdown hooks` 간의 시작 순서는 지정되지 않음
    - 즉 순서대로 실행을 보장할 수 없음
  - 모든 `shutdown hooks`가 실행된 후 JVM은 종료됨
- [api](https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/lang/Runtime.html#addShutdownHook(java.lang.Thread))의 사용 예시 참고





