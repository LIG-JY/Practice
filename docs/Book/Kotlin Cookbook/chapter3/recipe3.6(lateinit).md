# 지연 초기화를 위해 lateinit 사용하기

## 문제: 생성자의 속성 초기화를 위한 정보가 충분하지 않지만, 해당 속성을 nullable 하지 않게 선하고 싶다

## 해결: lateinit 변경자를 사용

- 널이 비허용으로 선언된 클래스 속성은 생성자에서 초기화 되어야함
- lateinit 변경자는 클래스 몸체에서만 선언됨
  - class 블록
- 사용자 정의 getter/setter가 없는 var 프로퍼티에만 사용 가능
- 코틀린 1.2부터 최상위 속성, 지역 변수에서도 사용 가능

```kotlin
data class Point(
    val x: Int,
    val y: Int
) {
    lateinit var name: String

    fun initName(name: String) {
        this.name = "default"
    }
}

fun main() {
    val point = Point(10, 20)
    println(point.name)
}

>>
Exception in thread "main" kotlin.UninitializedPropertyAccessException: lateinit property name has not been initialized
```

- 초기화 되기 전 lateinit 프로퍼티에 접근하면 UninitializedPropertyAccessException이 발생함
- 