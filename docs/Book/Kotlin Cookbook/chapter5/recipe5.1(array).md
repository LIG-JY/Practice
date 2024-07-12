# Array

- 코틀린에서 Array는 클래스
  - 코틀린에서는 Primitve type이 없다는 것을 기억하자

### [팩토리 메서드 arrayOf]

```kotlin
fun main() {
    val strings = arrayOf("this", "is", "bear")
}
```

- arrayOfNulls 메서드는 널로만 채워진 배열을 만들 수 있음
  - 배열에 널만 있음에도 배열의 원소의 타입을 선택해야함
  - 배열에 널이 아닌 것이 추가될 때 컴파일러가 확인할 수 있도록 미리 지정한다고 생각하면 됨

```kotlin
fun main() {
    val nullStrings = arrayOfNulls<String>(10)
}
```

### [Array의 생성자]

```kotlin
public inline constructor(size: Int, init: (Int) -> T)
```

- 2개의 매개변수를 받음
  - 크기
  - 초기화 함수 람다
- 람다는 배열을 생성할 때 인덱스마다 호출됨
  - 람다의 인자로 들어오는 Int는 인덱스

```kotlin
fun main() {
    val nullStrings = Array(5) { i -> (i + 1).toString() }
    nullStrings.forEach {
        println(it)
    }
}
>> 출력
1
2
3
4
5
```

### [primitive type의 배열에 대응하는 클래스]

- byteArrayOf, charArrayOf... 등등으로 primitive type에 대응하는 배열을 만들 수 있음

```kotlin
An array of bytes. When targeting the JVM, instances of this class are represented as byte[].
public class ByteArray(size: Int)
```

- 코틀린 클래스의 ByteArray에 대한 설명이다.
  - JVM에서 byte[]과 대응된다

### [indices 속성]

```kotlin
val nullStrings = Array(5) { i -> (i + 1).toString() }
nullStrings.indices.forEach { println(it) }
```

```kotlin
public val <T> Array<out T>.indices: IntRange
    get() = IntRange(0, lastIndex)
```

- 배열을 IntRange로 반환

### [withIndex 함수]

```kotlin
public fun <T> Array<out T>.withIndex(): Iterable<IndexedValue<T>> {
    return IndexingIterable { iterator() }
}

public data class IndexedValue<out T>(public val index: Int, public val value: T)
```

- 배열의 인덱스와 값을 같이 사용할 수 있음
  - IndexedValue라는 데이터 클래스 Iterable의 타입으로 사용함

```kotlin
fun main() {
    val nullStrings = Array(5) { i -> (i + 1).toString() }
    nullStrings.withIndex().forEach {
        println("index: " + it.index)
        println("value:" + it.value)
    }
}
>>출력
index: 0
value:1
index: 1
value:2
index: 2
value:3
index: 3
value:4
index: 4
value:5
```
