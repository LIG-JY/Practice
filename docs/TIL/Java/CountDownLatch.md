# CountDownLatch

## 요약

- `하나 이상의 스레드`가 다른 스레드에서 수행 중인 일련의 작업이 완료될 때까지 기다릴 수 있게 하는 동기화 보조 기능

## 동작

- 카운트 다운 초기화
    - CountDownLatch 개체가 생성될 때, 초기 카운트값을 설정함
    - 생성자의 매개변수로 초기 카운트값을 설정하도록 구현

```java
 public CountDownLatch(int count) {
        if (count < 0) throw new IllegalArgumentException("count < 0");
        this.sync = new Sync(count);
    }
```

- 대기
    - 카운트가 0이될 때 까지 await() 메소드를 호출한 모든 스레드를 대기(block)
    - 카운트가 0이 되면 await() 메소드 리턴, 호출한 모든 스레드가 계속 진행됨(released)

- 카운트 다운 감소
    - countDown()를 호출하면 카운트 값이 감소됨

## 사용 예시



## [non-public internal helper classes Sync]

- AbstractQueuedSynchronizer을 상속받아 구현한 Sync 클래스의 개체로 상태를 관리함

```java
private static final class Sync extends AbstractQueuedSynchronizer {
        private static final long serialVersionUID = 4982264981922014374L;

        Sync(int count) {
            setState(count);
        }

        int getCount() {
            return getState();
        }

        protected int tryAcquireShared(int acquires) {
            return (getState() == 0) ? 1 : -1;
        }

        protected boolean tryReleaseShared(int releases) {
            // Decrement count; signal when transition to zero
            for (;;) {
                int c = getState();
                if (c == 0)
                    return false;
                int nextc = c - 1;
                if (compareAndSetState(c, nextc))
                    return nextc == 0;
            }
        }
    }
```

### [생성자]

- count 값으로 상태를 설정함
- 상위 클래스 AbstractQueuedSynchronizer의 setState()를 호출해 state 멤버 변수를 초기화함
    - state 멤버 변수는 volatile 키워드가 붙어있음
        - 메모리 가시성
            - state 변수에 대한 쓰기 작업은 메인 메모리에서 이루어짐
            - 다른 모든 스레드가 이 변수에 대한 최신값을 볼 수 있음

### [`CountDownLatch.Sync` 클래스에서 `tryAcquireShared`]

- state 값이 0 이면 락(Sync 개체)을 획득할 수 있음
- 아니면 불가능

### [`CountDownLatch.Sync` 클래스에서 `tryReleaseShared`]

- getState() 로 얻은 count의 값이 0이될 때 까지 반복
- state 값(count)을 감소시킴
    - compareAndSetState 메서드를 통해 감소
    - 첫번째 매개변수(예상값)와 실제 값이 다르면 false로 return 문을 실행하지 않음
    - 예상값과 실제 값이 같으면 c - 1 값으로 업데이트 후 true를 반환
        - nextc 값을 0으로 초기화

- 참고로 매개변수로 입력받은 release 변수는 구현 상 사용되지 않음

## [await()]

- Causes the current thread to wait until the latch has counted down to zero, unless the thread is interrupted
- If the current count is zero then this method returns immediately
- count가 0보다 큰 상태면 await()를 호출한 스레드는 스케쥴링 목적으로 사용불가능(disabled) 상태가 됨
    - count가 0에 도달하면 dormant 상태에서 깨어남
    - interrupt 신호를 받으면 dormant 상태에서 깨어남

- 이 메소드를 실행하는 스레드가 이미 인터럽트 상태라면 InterruptedException이 발생하고, 인터럽트 상태 클리어
    - 인터럽트 플래그가 켜져있고, 인터럽트 처리 중에 await() 메소드 실행
- waiting 상태에서 인터럽트 신호를 받으면 InterruptedException이 발생하고, 인터럽트 상태 클리어
    - await() 상태가 호출되어, count > 0 으로 대기(waiting) 상태일 때 인터럽트 신호를 받는 경우

### 구현 // TODO 

```java
public void await() throws InterruptedException {
        sync.acquireSharedInterruptibly(1);
    }
```

- `acquireSharedInterruptibly()` 메서드를 통해 구현

```java
public final void acquireSharedInterruptibly(int arg)
        throws InterruptedException {
        if (Thread.interrupted() ||
            (tryAcquireShared(arg) < 0 &&
             acquire(null, arg, true, true, false, 0L) < 0))
            throw new InterruptedException();
    }
```

## [countDown()] // TODO