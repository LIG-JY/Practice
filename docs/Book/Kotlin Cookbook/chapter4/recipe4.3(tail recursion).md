# 꼬리 재귀

- 콜 스택에 새로운 스택 프레임을 추가하지 않게 구현할 수 있다.

```kotlin
import java.math.BigInteger

fun main() {
    println(factorial(100000))
}

@JvmOverloads
tailrec fun factorial(n: Long, acc: BigInteger = BigInteger.ONE): BigInteger =
    when (n) {
        0L -> BigInteger.ONE
        1L -> acc
        else -> factorial(n - 1, acc * BigInteger.valueOf(n))
    }
```

- 구현 방법은 다음과 같다.
  - @JvmOverloads로 자바에서도 default parameter가 포함된 함수를 호출할 수 있게 한다.
  - tailrec 키워드를 사용한다.
    - 컴파일러가 재귀를 최적화 해준다.
    - 반복문으로 바이트코드 생성
  - 재귀호출이 마지막 작업이어야함
    - 누적자에 값을 곱하고, 인자로 넘겨 재귀호출을 하기 때문에, 재귀호출이 가장 마지막 연산임

### [일반 재귀와 비교]

```kotlin
fun nonTailRecFactorial(n: Long): BigInteger =
    if (n == 0L) BigInteger.ONE
    else BigInteger.valueOf(n) * nonTailRecFactorial(n - 1)
```

```kotlin
tailrec fun tailRecFactorial(n: Long, acc: BigInteger = BigInteger.ONE): BigInteger =
    if (n == 0L) acc
    else tailRecFactorial(n - 1, acc * BigInteger.valueOf(n))
```

- 일반 재귀의 경우 재귀 호출이 끝나고, 곱하는 연산을 하게 된다.
  - 따라서 호출이 완료된 후 스택프레임을 유지해야함
- 꼬리 재귀의 경우 재귀 호출이 마지막 연산이라 스택 프레임을 유지할 필요가 없다.
