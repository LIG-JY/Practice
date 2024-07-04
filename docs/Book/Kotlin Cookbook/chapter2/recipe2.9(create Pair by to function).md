# to로 Pair 인스턴스 생성하기

## 문제: map의 entry로서 Pair 클래스의 인스턴스를 생성하고 싶다

## 해결: 중위(inflix) to 함수를 사용한다

```kotlin
public infix fun <A, B> A.to(that: B): Pair<A, B> = Pair(this, that)
```

- 제너릭 A,B를 통해 구현함
- 모든 제너릭 타입 A에 구현된 확장 함수

```kotlin
fun main() {
    val map = mapOf("A" to 1, "B" to 2, "C" to 3, Pair("D", 4)) // map의 entry로 사용
    val pair = "z" to 99
    val (x, y) = pair   // 구조 분해 할당
    println(x)
    println(y)
}
```

- map의 entry로 사용 예시
- 구조 분해 할당의 예시
