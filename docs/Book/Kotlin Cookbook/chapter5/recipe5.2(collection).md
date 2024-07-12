# 컬렉션 생성하기

### [가변/불변 구분]

- setOf, mapOf 등은 변경 불가능한 컬렉션을 생성
  - mutableSetOf 처럼 mutable이 붙어있으면 변경 가능한 컬렉션을 생성

```kotlin
public fun <T> listOf(vararg elements: T): List<T> = if (elements.size > 0) elements.asList() else emptyList()
```

- listOf의 구현을 보면, 반환값은 elements.asList()로 `asList()`가 붙어있음
  - asList()의 구현은 아래와 같다

```kotlin
/**
 * Returns a [List] that wraps the original array.
 */
public actual fun <T> Array<out T>.asList(): List<T> {
    return ArraysUtilJVM.asList(this)
}
```

- 불변(읽기전용) 컬렉션을 반환하는 것을 확인할 수 있다
  - JVM의 읽기 전용 리스트를 반환하는 Arrays.asList에 위임
