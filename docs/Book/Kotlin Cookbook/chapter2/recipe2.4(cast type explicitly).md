# 명시적으로 타입 변환하기

## 문제: 코틀린은 기본 타입을 더 큰 타입(Int -> Long)으로 승격하지 않음

## 해법: 구체적인 변환 프로세스가 필요함

```kotlin
fun main() {
    val intVar: Int = 3
    val longVar: Long = intVar // complie error: Type mismatch
}
```

- 코틀린은 기본 타입(Primitive)를 직접 제공하지 않음
  - 바이트 코드에서는 기본 타입으로 생성됨
- 자바의 wrapper 타입을 다루듯, 변환 메서드를 사용해야함

```kotlin
fun main() {
    val intVar: Int = 3
    val longVar: Long = intVar.toLong()
}
```

- toLong()과 같은 변환 메서드를 사용해서 컴파일 오류를 해결함

## [연산자 오버로딩]

- 아래와 같이 그냥 더해도 됨

```kotlin
fun main() {
    val intVar: Int = 3
    val longVar: Long = 3L + intVar
}
```

- 내부적으로 연산자 오버로딩이 되어있음
  - 값을 더해서 Long으로 반환하도록 처리함

```kotlin
 @kotlin.internal.IntrinsicConstEvaluation
    public operator fun plus(other: Int): Long
```

