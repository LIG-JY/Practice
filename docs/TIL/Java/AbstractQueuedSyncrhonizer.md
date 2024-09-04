# AbstractQueuedSynchronizer

- 대기 큐에 의존하는 `blocking locks`관련 기법을 제공하는 클래스
- 상태를 나타내기 위해 atomic int 값을 사용하는 대부분의 동기화 기법에 적용되도록 설계됨
- 하위 클래스에서 protected 접근 제어자가 붙은 메소드를 정의(구현)해야함
    - 이런 메소드들은 아래의 개념을 구현해야함
        - 상태를 변화시키는 것
        - 상태 변화가 하위 클래스의 개체(락 개념이 포함됨)를 획득하거나 해제하는 것과 연관되어야 함
- 하위 클래스에서 다른 상태 필드를 가질 수 있지만, 동기화 메커니즘에 관련된 상태는 atomic int 값에 의해 관리됨
    - atomic int 값은 getState(), setState(int) 및 compareAndSetState(int, int) 메서드를 통해 조작됨
- 하위 클래스는 non-public internal helper classes로 구현되어야 함
    - 이는 외부 클래스의 동기화 속성(state) 값을 구현하는데 사용됨

## blocking locks

- 동기화 기법의 일종
- `Blocking`은 어떤 스레드가 이 락(blocking lock)을 획득하기 위해 기다릴 때 다른 스레드가 락을 release할 때 까지 Block(대기)상태에 놓인다는 것을 의미함

## 하위 클래스 예시

- CountDownLatch의 non-public internal helper classes로 구현된 Sync 클래스

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

## protected int tryAcquireShared(int arg)

- `공유 모드`에서 락 획득을 시도하는 메서드
    - 락 개체가 `공유 모드`에서 획득하는 것을 허용하는 상태라면 개체(락)를 획득할 수 있음
- `tryAcquireShared` 메소드는 획득을 수행하는 스레드에서 호출됨
    - `tryAcquireShared`가 실패값을 반환하는 경우, AbstractQueuedSynchronizer를 구현한 개체는 호출한 스레드를 대기 큐에 넣음
        - 호출한 스레드가 이미 대기 큐에 있다면 넣지 않음
        - 다른 스레드가 개체를 release하는 메소드를 호출한 경우 큐에 있는 스레드의 대기 상태를 해제

### `CountDownLatch.Sync` 클래스에서 `tryAcquireShared`

- state 값이 0 이면 락(Sync 개체)을 획득할 수 있음
- 아니면 불가능

### [공유 모드]

- 동시에 여러 스레드가 리소스를 공유할 수 있는 모드

## protected boolean tryReleaseShared(int arg)

- `공유 모드`에서 락을 해제하는 것을 시도하는 메서드
- `tryReleaseShared` 메소드는 release를 수행하는 스레드에서 호출됨

### `CountDownLatch.Sync` 클래스에서 `tryReleaseShared`

- getState() 로 얻은 count의 값이 0이될 때 까지 반복
- state 값(count)을 감소시킴
    - compareAndSetState 메서드를 통해 감소
    - 첫번째 매개변수(예상값)와 실제 값이 다르면 false로 return 문을 실행하지 않음
    - 예상값과 실제 값이 같으면 c - 1 값으로 업데이트 후 true를 반환
        - nextc 값을 0으로 초기화

- 참고로 매개변수로 입력받은 release 변수는 구현 상 사용되지 않음 