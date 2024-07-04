# 코틀린에서 널 허용 타입 사용하기

## val 과 smart casting

```kotlin
class Person(
        val first: String,
        val middle: String?,
        val last: String,
    )

    val p1 = Person("john", "mom", "last")
    val p2 = Person("john", null, "last")
    if (p2.middle != null) {
        val middleNameLength = p2.middle.length
    }
```

- p2.middle은 String? -> String 으로 스마트 캐스팅 됨
- p2가 val로 선언되었기 때문에 스마트 캐스팅이 가능함
  - p2는 한번 값이 설정되면 값이 변하지 않기 때문

```kotlin
class Person(
        val first: String,
        val middle: String?,
        val last: String,
    )

    val p1 = Person("john", "mom", "last")
    var p2 = Person("john", null, "last")
    if (p2.middle != null) {
        val middleNameLength = p2.middle.length // compile error
    }
```

- Smart cast to 'String' is impossible, because 'p2.middle' is a complex expression
- 변수 p2가 정의된 시점과 p2의 속성 middle에 접근하는 시점 중간에 값이 변경되었을 수도 있기 때문에, 스마트 캐스팅이 불가능함

## 안전 호출 연산자(safe call) 사용하기

```kotlin
class Person(
        val first: String,
        val middle: String?,
        val last: String,
    )

    val p1 = Person("john", "mom", "last")
    var p2 = Person("john", null, "last")
    if (p2.middle != null) {
        val middleNameLength = p2.middle?.length
    }
```

- 스마트 캐스팅이 안 되는 경우 안전 호출 연산자(?.)를 사용하면 좋음
- short-circuit 으로 작동함
  - p2.middle == null 인 경우 평가를 종료하고, middleNameLength는 null이 됨
  - p2.middle != null 인 경우 p2,middle.length 까지 평가해서 middleNameLength에 대입
- middleNameLength의 타입은 Int?

## 안전 호출 연산자와 엘비스 연산자(?:)를 병행

```kotlin
class Person(
        val first: String,
        val middle: String?,
        val last: String,
    )

    val p1 = Person("john", "mom", "last")
    var p2 = Person("john", null, "last")
    if (p2.middle != null) {
        val middleNameLength = p2.middle?.length ?: 0
    }
```

- middleNameLength의 타입은 Int?이라 유효한 값으로 사용하기 위해서 엘비르 연산자를 사용하자
- 엘비스 연산자는 왼쪽의 값이 널이면 오른쪽의 값을 반환함
  - p2.middle == null의 경우 0을 리턴
  - p2.middle != null의 경우 p2.middle의 값을 리턴

## 안전 타입 변환 연산자(as?)

```kotlin
val p1 = p2 as? Person
```

- 타입 변환이 올바르게 작동하지 않는 경우 ClassCastException이 발생하는 대신 null을 반환
  -  as 연산자를 사용할 때 변환이 실패하면 ClassCastException 예외가 발생
- 변환 실패했을 경우 null에 대한 처리를 하면 됨
- 예외를 줄이고, 타입 변환이 실패할 수 있다는 의도를 명확하게 해준다는 장점이 있음
