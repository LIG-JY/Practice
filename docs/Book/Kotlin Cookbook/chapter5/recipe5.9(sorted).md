# 정렬

- 기준을 차례차례 적용해서 정렬할 수 있다.

```kotlin
data class Golfer(val score: Int,
                  val first: String,
                  val last: String)

fun main() {
    val golfers = listOf(
        Golfer(70, "Jack", "Nicklaus"),
        Golfer(68, "Tom", "Watson"),
        Golfer(68, "Bubba", "Watson"),
        Golfer(70, "Tiger", "Woods"),
        Golfer(68, "Ty", "Webb")
    )

    // Sort by properties
    val sorted = golfers.sortedWith(
        compareBy({ it.score }, { it.last }, { it.first })
    )

    sorted.forEach { println(it) }
}
```

- 데이터 클래스를 정렬할 때, 정렬 기준의 우선 순위를 정할 수 있다.

```kotlin
public fun <T> Iterable<T>.sortedWith(comparator: Comparator<in T>): List<T> {
    if (this is Collection) {
       if (size <= 1) return this.toList()
       @Suppress("UNCHECKED_CAST")
       return (toTypedArray<Any?>() as Array<T>).apply { sortWith(comparator) }.asList()
    }
    return toMutableList().apply { sortWith(comparator) }
}
```

- sortedWith의 구현은 위와 같다.
  - 참고로 stable 정렬을 만족한다. 
    > The sort is stable. It means that equal elements preserve their order relative to each other after sorting.
  - return의 sortWith은 java.util.Collections.sort()을 호출한다.

### [compareBy 구현]

```kotlin
public fun <T> compareBy(vararg selectors: (T) -> Comparable<*>?): Comparator<T> {
    require(selectors.size > 0)
    return Comparator { a, b -> compareValuesByImpl(a, b, selectors) }
}
```

- compareBy는 매개변수로 selectors: (T) -> Comparable<*>? 람다식을 여러개 받을 수 있다.
  - 각 람다식은 T의 객체를 입력받아 Comparable<*>? 타입을 반환한다.
- 여기 예시에서는 람다식 { it.score }, { it.last }, { it.first } 을 받아 Comparator을 생성한다.
  - it.score은 Comparable<Int>, it.last와 it.first는 Comparable<String>을 반환함
- Comparable<*>? 타입은 nullable 하고, 모든 타입에 대한 Comparable을 일반화 함(와일드 카드)
- 즉 compareBy 함수는 비교 선택자(selector)로 어떤 타입이든 입력받을 수 있다.

- Comparator은 함수형 인터페이스다.
  - [참고](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin/-comparator/)
  - 즉 단일 추상 메서드(SAM: Single Abstract Method)를 가지는 인터페이스다.
  - 문서를 참조하면 유일한 추상메서드는 abstract fun compare(a: T, b: T): Int
  - 이 추상메서드 compare의 구현이 Comparator 뒤의 람다 { a, b -> compareValuesByImpl(a, b, selectors) }

[TODO: 여기서부터~]

### [Comparator의 확장 메서드로 정렬하기]

- thenBy는 Comparator을 만드는 함수다.
  - 함수형 인터페이스 Comparator의 확장 함수 중 하나임

```kotlin
@kotlin.internal.InlineOnly
public inline fun <T> Comparator<T>.thenBy(crossinline selector: (T) -> Comparable<*>?): Comparator<T> =
    Comparator { a, b ->
        val previousCompare = this@thenBy.compare(a, b)
        if (previousCompare != 0) previousCompare else compareValuesBy(a, b, selector)
    }
```
- 이전 비교 후에 새로운 비교 기준을 적용한다

### [crossline 키워드]