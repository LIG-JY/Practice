# 지원(위임) 속성 기법

## 문제: 클래스의 속성(프로퍼티)를 외부에 노출하고 싶지만, 해당 속성을 set, get할 때 제어가 필요함

## 해결: 같은 타입의 속성을 하나 더 정의하여 setter, getter을 위임하기

```kotlin
class Customer(val name: String) {
    private var _messages: List<String>? = null // private 접근 제어자로 노출을 막음

    val messages: List<String> // 외부로 노출되는 위임 속성
        get() {
            if (_messages == null) {
                this._messages = loadMessages()
            }
            return _messages!!
        }

    private fun loadMessages(): MutableList<String> =
        mutableListOf(
            "Initial contact",
            "Convinced them to use Kotlin",
            "Sold training class, Sweet."
        ).also { println("Loaded messages") }
}

fun main() {
    val customer = Customer("july")
    println(customer.messages)
    println(customer.messages)
}

>> 출력
Loaded messages
[Initial contact, Convinced them to use Kotlin, Sold training class, Sweet.]
[Initial contact, Convinced them to use Kotlin, Sold training class, Sweet.]
```

- _messages 프로퍼티에는 접근할 수 없음
- message 프로퍼티가 역할을 위임 받고, 여기에는 접근할 수 있음
- Load messages 가 한 번 출력됬음
  - getter가 호출될 때 조건에 따라 load는 한 번만 하도록 구현

### [lazy 대리자 함수]

```kotlin
class Customer(val name: String) {
    private val _messages: List<String> by lazy { loadMessages() } // private 접근 제어자로 노출을 막음

    val messages: List<String> // 외부로 노출되는 위임 속성
        get() {
            return _messages
        }

    private fun loadMessages(): MutableList<String> =
        mutableListOf(
            "Initial contact",
            "Convinced them to use Kotlin",
            "Sold training class, Sweet."
        ).also { println("Loaded messages") }
}
```

- lazy 대리자 함수를 사용해 지연 로딩을 구현
  - 수정 전 예시 똑같이 작동함
- 속성에 처음으로 접근할 때 까지 초기화를 지연함
    - 따라서 처음으로 속성에 접근할 때 한 번 loadMessages()로 초기화