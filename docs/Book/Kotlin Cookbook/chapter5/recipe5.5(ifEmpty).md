# 컬렉션이 빈 경우 기본값 리턴하기

- ifEmpty, ifBlank은 컬렉션, 문자열이 비어있을 때  기본값을 리턴

```kotlin
fun main() {
    val list = listOf('a', 'b', 'c', 'd', 'e', 'f')
    val res = list.filter { it > 'c' }.map { it - 32 }.joinToString(separator = ", ")
    println(res)
    val emptyRes = list.filter { it < 'a' }.map { it - 32 }.joinToString(separator = ", ").ifEmpty { "E" }
    println(emptyRes)
    val emptyRes2 = list.filter { it < 'a' }.ifEmpty { listOf('e') }.map { it - 32 }.joinToString(separator = ", ")
    println(emptyRes2)
}

```

- ifEmpty를 필터후 바로 사용해도 됨
  - filter의 결과도 마찬가지로 collection
- joinToString() 후 사용해도 됨
  - 문자열(CharSequence)에도 ifEmpty 함수를 지원함

```kotlin
@SinceKotlin("1.3")
@kotlin.internal.InlineOnly
public inline fun <C, R> C.ifEmpty(defaultValue: () -> R): R where C : CharSequence, C : R =
    if (isEmpty()) defaultValue() else this

```

- C: CharSequence 객체를 일반화
- R: return 반환값의 타입
- where C : CharSequence, C : R
  - C는 CharSequence이며, 동시에 R타입이여야 함
  - 즉 ifEmpty의 수신 객체와 반환값의 타입이 같음
  - 수신 객체는 CharSequence 인터페이스와 호환되는 타입
    - String
    - StringBuffer
    - StringBuilder