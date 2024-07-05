# const와 val의 차이 이해하기

## 문제: 컴파일 타임에 변수가 상수임을 나타내야 함

## 해법: const 변경자(modifier)을 사용함

- 컴파일 타임 상수는 반드시 객체나 동반 객체(companion object) 선언의 최상위 멤버
  - 프로그램이 실행 전 초기화하기 위함
- 컴파일 타임 상수는 문자열 또는 기본 타입의 래퍼 클래스
  - Byte, Short, Int, Long, Float, Double, Char, Boolean
- 컴파일 타임 상수는 사용자가 정의한 커스텀 getter을 가질 수 없음

```kotlin
class Task(
    val name: String,
    priorityValue: Int = DEFAULT_PRIORITY,
) {

    companion object {
        const val MIN_PRIORITY = 1
        const val MAX_PRIORITY = 5
        const val DEFAULT_PRIORITY = 3
            get() {
                return DEFAULT_PRIORITY
            } // 컴파일 오류: Const 'val' should not have a getter
    }

    var priority: Int = validPriority(priorityValue)
        set(value) {
            field = validPriority(value)
        }

    private fun validPriority(priority: Int): Int {
        return priority.coerceIn(MIN_PRIORITY, MAX_PRIORITY)
    }

}
```

- companion object는 클래스가 로드될 때 한 번 초기화 됨
- 커스텀 setter는 멤버 변수를 수정할 때 마다 호출 됨
- 생성자에서 val이 붙은 매개변수는 클래스의 멤버 변수에 포함됨
- 생성자에서 val이 붙지 않은 매개변수는 객체 생성 시 지역 변수로 값만 복사되어 사용됨

### [코드 확인]

```kotlin
fun main() {
    val task = Task("task1", 2) // 1)
    val task2 = Task("task1", 75) //2 )
    task.priority = 8 // 3)
}
```

- 1) val task = Task("task1", 2)
  - JVM이 Task 클래스를 처음으로 참조하는 상황
    - 클래스 로드 시점
  - companion object 초기화
  - 생성자 호출
    - 멤버 변수 name의 값 초기화
    - 생성자의 지역 변수 priorityValue값 초기화(매개변수로 넘어온 값 복사)
  - 객체의 멤버 초기화
    - var priority를 초기화
    - 내부의 validPriority 호출
- 2) val task2 = Task("task1", 75)
  - companion object를 초기화 하지 않음
  - 나머지 과정은 동일함
- 3) priority 멤버의 커스텀 setter 호출
    - priority 값 변경