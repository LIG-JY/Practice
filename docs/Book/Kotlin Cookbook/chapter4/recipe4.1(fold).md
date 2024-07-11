# fold

## 문제: 시퀀스, 컬렉션을 하나의 값으로 축약하고 싶다.

```kotlin
public inline fun <T, R> Iterable<T>.fold(initial: R, operation: (acc: R, T) -> R): R {
    var accumulator = initial
    for (element in this) accumulator = operation(accumulator, element)
    return accumulator
}
```

- 2개의 인자
  - 초기값
  - 누적해서 새로운 값을 리턴하는 함수

- 사용 예는 다음과 같음

```kotlin
fun main() {
    val list = listOf(1,2,3,4,5)
    val sum = list.fold(0) { acc, i -> acc + i }
    println(sum)
}
>> 출력
15
```

- 참고로 람다 표현식을 함수의 마지막 매개변수로 전달할 때, 괄호 밖으로 뺄 수 있음

### [fold 내부 동작]

```kotlin
fun main() {
    val list = listOf(1,2,3,4,5)
    val sum = list.fold(0) { acc, i ->
        println("acc = $acc, i = $i")
        acc + i
    }
    println(sum)
}
>> 출력
acc = 0, i = 1
acc = 1, i = 2
acc = 3, i = 3
acc = 6, i = 4
acc = 10, i = 5
15
```

- acc값은 fold의 첫번째 인자로 초기화 됨
- 반복할 때 마다 acc = acc + i
- 참고로 초기값 0은 이 람다 연산(더하기)의 함등원임
  - 원래 더하기 연산에서 0이 항등원이기 때문
  - 초기값 0은 컬렌션의 합을 구하는 연산의 결과에 영향을 주지 않음

### [재귀 함수 예제]

```kotlin
import java.math.BigInteger

fun main() {
    println(recursiveFactorial(5))
}

fun recursiveFactorial(n: Int): BigInteger {
    return when (n) {
        0, 1 -> BigInteger.ONE
        else -> BigInteger(n.toString()) * recursiveFactorial(n - 1)
    }
}
>> 출력
120
```

- 참고로 java.math.BigInteger의 오버로딩된 생성자 중에서 코틀린의 Int타입을 인자로 받는 생성자가 없기 때문에 toString()으로 문자열로 변환해서 대입함
- fold를 이용하면 아래와 같이 펙토리얼 함수를 구현할 수 있다

```kotlin
fun foldFactorial(n: Int): BigInteger {
    return when (n) {
        0, 1 -> BigInteger.ONE
        else -> (2..n).fold(BigInteger.ONE) {acc, i -> acc * BigInteger(i.toString()) }
    }
}
```
