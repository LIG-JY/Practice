# Volatile

## Visibility Guarantee

- The Java `volatile` keyword is intended to address `variable visibility problems`.
    - all writes to the `volatile` variable will be written back to main memory immediately
    - Also, all reads of the `volatile` variable will be read directly from main memory.
- Declaring a variable `volatile thus guarantees the visibility for other threads of writes to that variable.

### Full volatile Visibility Guarantee

- Actually, the visibility guarantee of Java volatile goes beyond the volatile variable itself.
    1. If Thread A writes to a volatile variable and Thread B subsequently reads the same volatile variable, then all
       variables visible to Thread A before writing the volatile variable, will also be visible to Thread B after it has
       read the volatile variable.
    2. If Thread A reads a volatile variable, then all variables visible to Thread A when reading the volatile
       variable will also be re-read from main memory

```java
// 예시 1

public class MyClass {
    private int years;
    private int months
    private volatile int days;


    public void update(int years, int months, int days){
        this.years = years;
        this.months = months;
        this.days = days;
    }
}
```

- 쓰기 메모리 베리어
    - volatile 변수에 값을 쓰기 전에, 해당 쓰기 작업 이전에 발생한 모든 쓰기 작업이 메인 메모리에 반영됨
- update() 메서드에서 years, months 변수가 업데이트 되고 나서, days 변수가 업데이트 됨
- days는 volatile variable 이라 `Full volatile Visibility Guarantee`이 보장됨
- days 변수에 쓰기 작업하기 전 볼 수 있었던 변수들(years, days) 또한 메인 메모리에 써지고 업데이트 됨
- 따라서 다른 스레드에서도 years, days의 최신값을 볼 수 있음
    - volatile keyword가 붙지 않은 변수의 가시성도 보장할 수 있기에 `Full`이라는 표현을 사용

```java
// 예시 2

public class MyClass {
    private int years;
    private int months
    private volatile int days;

    public int totalDays() {
        int total = this.days;
        total += months * 30;
        total += years * 365;
        return total;
    }

    public void update(int years, int months, int days){
        this.years  = years;
        this.months = months;
        this.days   = days;
    }
}
```

- 읽기 메모리 베리어
    - volatile 변수 값을 읽기 전에, 해당 읽기 작업 이후에 발생한 모든 읽기 작업이 메인 메모리에서 최신값을 얻음
- totalDays() 메서드에서 days 변수를 읽고 months, years 변수를 읽음
- days는 volatile variable 이라 `Full volatile Visibility Guarantee`이 보장됨
- days 변수를 읽고 난 후 읽기 연산이 적용되는 변수들(months, years)는 메인 메모리에서 최신 값을 읽어옴

## `volatile` is Not Always Enough

- Thread 1만 쓰기를 하고 Thread 2는 읽기만 할 때, volatile 키워드가 최신 값을 보장
    - 메인 메모리에 쓰기 때문
- 여러 스레드가 공유 volatile 변수에 쓰기를 수행해도, 새로운 값이 이전 값에 의존하지 않는다면 메인 메모리에 올바른 값이 저장될 수 있음
    - 즉, 스레드가 공유 volatile 변수에 값을 쓰기 전에 먼저 그 값을 읽을 필요가 없다면 문제 없음
    - 새로 쓰는 값이 이전의 값에 의존하지 않는 경우
- 스레드가 먼저 volatile 변수의 값을 읽고, 그 값을 기반으로 새로운 값을 생성해야 하는 경우, volatile 변수만으로는 올바른 동기화와 가시성을 보장할 수 없음
    - volatile 변수를 읽고 새로운 값을 쓰기까지의 짧은 시간 간격 동안, 여러 스레드가 동일한 값을 읽고 새로운 값을 생성하며, 이를 메인 메모리에 쓰는 과정에서 서로의 값을 덮어쓸 수 있는 race
      condition이 발생할 수 있음

## When is volatile Enough?

- Reading or writing a volatile variable does not block threads reading or writing
- In case only one thread reads and writes the value of a volatile variable and other threads only read the variable,
  then the reading threads are guaranteed to see the latest value written to the volatile variable.
  - volatile 변수의 새로운 값이 이전의 값에 의존하지 않는 경우 적절함

## `AbstractQueuedSynchronizer` 의 멤버 변수 state와 `volatile`

- AbstractQueuedSynchronizer`은 `volatile` 키워드로 충분함
- state의 새로운 값이 이전의 값에 의존하기 않기 때문
  - setState() 메서드는 매개변수로 받은 값으로 덮어 쓰도록 구현

```java
protected final void setState(int newState) {
        state = newState;
    }
```

## reference

https://jenkov.com/tutorials/java-concurrency/volatile.html

https://jpbempel.github.io/2015/05/26/volatile-and-memory-barriers.html