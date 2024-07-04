# Int,Long을 거듭제곱하는 함수 확장함수로 만들기

## 문제: 코틀린에서 Int, Long을 거듭제곱하는 함수를 제공하지 않음

## 해결: 확장 함수를 정의

```kotlin
fun main() {
    val intVar: Int = 3
    val res = intVar.pow(3)
    println(res)
}

fun Int.pow(exponent: Int): Int {
    return this.toDouble().pow(exponent).toInt()
}
```

- 확장 함수를 만드는 법은 아래와 같음

```kotlin
fun 수신객체타입.함수이름(매개변수: 타입): 반환타입 {
    // 함수 본문
}
```

- 함수 본문에서 this는 수신객체
- 확장 함수가 기존 메서드와 충돌할 경우, 기존 메서드가 우선순위를 가짐