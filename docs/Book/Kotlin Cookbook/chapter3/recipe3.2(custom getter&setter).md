# 사용자 정의 getter & setter 생성하기

## 문제: getter, setter을 사용자 정의하고 싶음

## 해법: 클래스의 멤버 변수에 get과 set함수를 추가

- 코틀린 클래스의 멤버는 기본적으로 public
- 데이터 은닉 원칙을 위해 코틀린 클래스에서 멤버 변수를 직접 선언할 수 없음
  - 대신 프로퍼티로 멤버 변수를 선언함
  - 컴파일러가 자동으로 getter/setter을 만들어 주는 개념

### 프로퍼티

```kotlin
class Task(
    val name: String
) {
    var priority = 0
}

fun main() {
    val task = Task("task1")
    println(task.priority) // getter 호출
    task.priority = 5   // setter 호출
    println(task.priority)  // getter 호출
    println(task.name)  // getter 호출
}

>> 출력
0
5
task1
```

- 주 생성자에서 선언한 name, 클래스 블록 내부에서 선언한 priority 모두 프로퍼티
- priority 프로퍼티의 경우 개체를 생성할 때 priority에 값을 대입할 수 없음

### 주 생성자로 선언하지 않은 프로퍼티의 값을 수정하기

```kotlin
fun main() {
    val task = Task("task1").apply { priority = 3 } // setter 호출
    println(task.priority) // getter 호출
}
```

- 객체 생성 후, apply를 사용해서 프로퍼티의 값을 수정
  - 내부에서 setter 호출

### backing field(지원 필드)

```kotlin
class Task(
    val name: String
) {
    var priority = 0 
        set(value) {
            field = if (value > 0) value
            else 0
        }
}
```

- 프로퍼티의 setter, getter에서 사용하는 필드를 참조하는 변수
  - 변수명은 field
