# 자바를 위한 메소드 중복

## 문제: default parameter을 가진 코틀린 함수가 있는데, 자바에서 각 파라미터의 값을 직접적으로 명시하지 않고 해당 코틀린 함수를 호출하고 싶다

## 해법: @JvmOverloads 어노테이션을 해당 함수에 추가한다.

- 자바는 메소드 기본 인자를 지원하지 않음
- kotlin은 메소드 기본 인자를 지원
- @JvmOverloads를 함수에 붙이면 기본 인자에 따라 Kotlin 컴파일러가 함수 오버로딩으로 바이트 코드를 생성함

```kotlin
class Example {
    @JvmOverloads
    fun greet(name: String = "World", greeting: String = "Hello") {
        println("$greeting, $name!")
    }
}
```

```java
public final class Example {
    public final void greet(String name, String greeting) {
        System.out.println(greeting + ", " + name + '!');
    }

    public final void greet(String name) {
        greet(name, "Hello");
    }

    public final void greet() {
        greet("World", "Hello");
    }
}
```

- 이 기능은 Java, Kotlin을 함께 쓰는 프로젝트에서 유용함
- 특히 생성자 오버로딩을 구현할 때 유용함

## reference

https://medium.com/@mmlodawski/https-medium-com-mmlodawski-do-not-always-trust-jvmoverloads-5251f1ad2cfe
https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.jvm/-jvm-overloads/