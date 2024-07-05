# Nothing

## 절대 리턴하지 않는 함수에 Nothing을 사용하기

- 결코 존재할 수 없는 값을 나타냄

```kotlin
public class Nothing private constructor()
```

- Nothing 클래스의 구현
  - private 생성자는 외부에서 인스턴스화 할 수 없다는 것을 의미함
  - 클래스 내부에서도 인스턴스화 코드는 존재하지 않음
    - 즉 Nothing의 개체는 존재하지 않음
- Nothing은 크게 2가지 상황에서 사용
  - 예외를 던지는 경우
  - 변수에 null을 대입할 때

### [예외를 던질 때 Nothing]

```kotlin
fun doNothing(): Nothing {
    throw RuntimeException()
}
```

- 이 함수는 예외를 던지기 때문에 리턴하지 못함
- 자바와 다르게 예외 때문에 리턴 타입이 변경될 수 있음을 보여주는 사례

### [변수에 null할 때 Nothing]

```kotlin
fun main() {
    val a = null
}
```

- 변수에 null을 대입하고, 구체적인 타입을 명시하지 않으면 컴파일러는 Nothing?로 추론함
- Nothing은 모든 타입의 하위 타입으로 간주함

```kotlin
fun main() {
    for (n in 1..10) {
        val x = when (n % 3) {
            0 -> "$n % 3 == 0"
            1 -> "$n % 3 == 1"
            2 -> "$n % 3 == 2"
            else -> throw Exception("Houston, we have a problem...")
        }
        if (x is String) {
            println("true")
        }
    }
}
```

- 논리 상 n % 3의 값은 0,1,2 뿐이지만, 컴파일러는 이를 알 수 없음
- when문의 문법 때문에 else절에 예외를 추가
- 예외가 발생할 일이 없지만 발생할 경우 Nothing이고, 이는 String의 하위 타입으로 간주됨 