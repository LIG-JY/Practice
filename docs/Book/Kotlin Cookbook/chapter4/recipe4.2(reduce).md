# reduce

## 문제: 컬렉션의 값을 축약하고 싶지만, 초기값을 설정하고 싶지 않다.

- fold와 다르게 초기값을 설정하지 않는다.
- 따라서 컬렉션의 첫번째 원소가 초기값이다.
- 컬렉션이 빈 경우 예외가 발생함
  - 컬렉션이 빌 가능성이 있는 경우 reduce 대신 reduceOrNull을 사용하자

```kotlin
public inline fun <S, T : S> Iterable<T>.reduce(operation: (acc: S, T) -> S): S {
    val iterator = this.iterator()
    if (!iterator.hasNext()) throw UnsupportedOperationException("Empty collection can't be reduced.")
    var accumulator: S = iterator.next()
    while (iterator.hasNext()) {
        accumulator = operation(accumulator, iterator.next())
    }
    return accumulator
}
```

- 참고로 val iterator을 초기화할 때 this.iterator()은 첫번째 원소가 아님
  - next()를 한 번 호출해야 첫번째 원소

### [reduce를 사용할 때 주의할 점]

- 원래의 의도는 reduce로 컬렉션의 값을 축약할 때 2를 곱해서 더하고 싶다.

```kotlin
fun main() {
    val nums = listOf(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
    nums.reduce { acc, i ->
        println("acc: $acc i: $i")
        acc + i * 2
    }
}
>> 출력
acc: 1 i: 2
acc: 5 i: 3
acc: 11 i: 4
acc: 19 i: 5
acc: 29 i: 6
acc: 41 i: 7
acc: 55 i: 8
acc: 71 i: 9
acc: 89 i: 10
```

- 첫번째 원소 i는 그냥 더했다.
  - 첫번째 원소는 acc를 초기화할 때 사용되 i에 포함된 적이 없음
- 이런 경우 fold를 사용하는 것이 적절하다

### [Java 스트림과 비교]

- Java 스트림에도 reduce 메소드가 2개 있다.
  - 하나는 바이너리 연산자(람다)만 받는 메소드
  - 하나는 바이너리 연산자와 초기값을 받는 메소드
- 코틀린에서 바이너리 연산자만 받는 메소드를 fold에 대응했다고 볼 수 있다.
  - 참고로 초기값을 받지 않고, 바이너리 연산자만 받는 Java의 스트림은 컬렉션이 빈 경우 Optional을 반환한다.

```Java
Optional<T> reduce(BinaryOperator<T> accumulator)
T reduce(T identity, BinaryOperator<T> accumulator)
```

