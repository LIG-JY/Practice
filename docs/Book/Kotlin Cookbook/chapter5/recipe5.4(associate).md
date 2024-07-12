# 컬렉션에서 맵 만들기

- associat 함수에 대해서 알아보자
- 한 묶음의 키가 있고, 키로 생성된 값으로 맵을 만들고 싶다면 associate 함수를 사용하면 된다

```kotlin
fun main() {
    val key = 'a'..'f'
    val map = key.associate { it to it.uppercaseChar() }
    map.forEach { println(it) }
}
>> 출력
a=A
b=B
c=C
d=D
e=E
f=F
```

```c++
public inline fun <T, K, V> Iterable<T>.associate(transform: (T) -> Pair<K, V>): Map<K, V> {
    val capacity = mapCapacity(collectionSizeOrDefault(10)).coerceAtLeast(16)
    return associateTo(LinkedHashMap<K, V>(capacity), transform)
}
```

- associate의 유일한 매개변수로 람다를 입력받음
  - 람다는 T를 Pair<K,V>로 변환함

```kotlin
fun main() {
    val key = 'a'..'f'
    val map = key.associateWith { it.uppercaseChar() }
    map.forEach { println(it) }
}
```

- associatedWith는 동일한 동작을 하지만, 더 간편하다.
- 