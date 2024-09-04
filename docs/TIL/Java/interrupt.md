# java.lang.Thread.interrupt()

## 인터럽트란?

- 하나의 스레드가 다른 스레드의 작업을 중단시키고자 할 때 사용하는 메커니즘
    - `Thread.interrupt() 메소드`를 호출해 해당 스레드에 인터럽트 신호를 보낼 수 있음
- 일반적인 경우 `Thread.interrupt() 메소드`를 호출하면 인터럽트 상태가 설정됨
  - 예외 케이스가 아래의 blocking 상태일 때

### 스스로 인터럽트

- Thread.currentThread().interrupt()를 호출하는 방식으로 현재 실행 중인 스레드가 자기 자신에게 인터럽트 신호를 보낼 수 있음
    - 스레드가 자기 자신을 인터럽트하는 것은 언제나 가능함

### 다른 스레드를 인터럽트

- 다른 스레드에게 인터럽트 신호를 보낼
  때 [security manager](https://docs.oracle.com/javase%2Ftutorial%2F/essential/environment/security.html)의 제약이 있을 수 있음
  - security manager은 checkAccess() 메서드로 다른 스레드에 접근 권한이 있는지 확인
  - 권한이 없으면 SecurityException 예외를 던짐

### 인터럽트 상태(interrupt status)

- 내부적으로 인터럽트 상태를 플래그로 구현함
  - 인터럽트 신호를 받으면 인터럽트 상태가 설정됨
  - 스레드에서 인터럽트가 처리되는 동안 이 플래그가 설정되어 있음
  - 인터럽트 처리가 완료되면 클리어됨(interrupt status cleared)
- wait(), join(), slee() 등 메서드로 스레드가 blocking 상태일 때 인터럽트 신호를 받는다면 blocking 상태를 종료하고 인터럽트 처리가 완료됨
  - 인터럽트 상태가 설정되지 않고 바로 인터럽트 플래그 cleared
  - InterruptedException을 던짐

## reference

https://docs.oracle.com/javase/8/docs/api/java/lang/Thread.html#interrupt--

https://docs.oracle.com/javase%2Ftutorial%2F/essential/environment/security.html

