# 연산자 중복

## 문제: 연산자를 정의하고 싶음

## 해결: 연산자 오버로딩을 사용해 커스텀 연산자를 구현

```kotlin
data class Point(
    val x: Int,
    val y: Int
) {
    operator fun unaryMinus(): Point {
        return Point(-x, -y) // 단항 연산자 minus 정의
    }
}

fun main() {
    val point = Point(10, 20)

    println(-point)
}

>> 출력
Point(x=-10, y=-20)
```

### [자신이 작성하지 않은 클래스에 연산자 관련 함수를 추가하기]

- 확장 함수(extension function) 사용하기

```kotlin
import org.apache.commons.math3.complex.Complex

operator fun Complex.plus(c: Complex) = this.add(c)
operator fun Complex.minus(c: Complex) = this.subtract(c)

```

- 아파치의 Math 라이브러리의 Complex 클래스의 연산자를 오버로딩
- 실행 시 대응되는 자바 클래스의 기존 메서드(add, substract)에 연산을 위임함

### [프로퍼티 참조]

```kotlin
data class Point(
    val x: Int,
    val y: Int
) {
    lateinit var name: String

    fun initName() {
        this.name = "default"
        println(::name.isInitialized)
    }
}
```

- 특정 프로퍼티에 참조하는 기능
    - ::name
- KProperty 객체를 반환
- isInitialized 메서드를 통해 프로퍼티의 초기화 여부를 boolean 결과로 확인할 수 있음

## reference

https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.reflect/-k-property/