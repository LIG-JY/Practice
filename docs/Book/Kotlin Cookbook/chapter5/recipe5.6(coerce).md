# 주어진 범위로 값 강제하기

- 값이 주어졌을 때, 값이 특정 범위 안에 들면 해당 값을 리턴하고 그렇지 않다면 범위의 최솟값 또는 최대값을 리턴할 수 있다.
  - 이 때 값이 특정 범위를 벗어났을 때 최소값에 가깝냐, 최대값에 가깝냐에 따라 범위가 결정됨
- range의 coerceIn 함수의 사용법을 알아보자

```kotlin
fun main() {
    val min = 4
    val max = 23
    val range = min..max

    println(30.coerceIn(range))
}
>> 출력
23
```
