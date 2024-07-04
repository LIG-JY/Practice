# 자바에 널 허용 지시자 추가하기

## 문제: 코틀린 코드가 자바 코드와 상호 작용이 필요하고, 널 허용성 어노테이션을 강제하고 싶을 때

## 해법: 컴파일 타임 파라미터 Xjsr305=strict 사용하기

- 많은 라이브러리가 JSR-305 호환 어노테이션을 사용 중
    - 대표적으로 스프링 프레임워크
- "-Xjsr305=strict" 옵션을 사용하면 JSR-305 애너테이션 (@Nonnull, @Nullable, 등)이 적용된 Java 코드를 Kotlin에서 사용할 때, Kotlin 컴파일러가 이를 엄격하게
  해석함
- 예를 들어 아래와 같이 자바와 호환됨

```java
import javax.annotation.Nonnull;
import javax.annotation.Nullable;

public class JavaClass {

    @Nonnull
    public String getNonNullString() {
        return "Hello, World!";
    }

    @Nullable
    public String getNullableString() {
        return null;
    }
}
```

```kotlin
fun main() {
    val javaClass = JavaClass()

    // getNonNullString은 Non-null로 취급되며 null 할당이 불가능
    val nonNullString: String = javaClass.getNonNullString()

    // getNullableString은 Nullable로 취급되며 null 할당이 가능
    val nullableString: String? = javaClass.getNullableString()

    // 다음 줄은 컴파일 타임 오류를 발생시킴
    // val nonNullStringError: String = javaClass.getNullableString()
}
```

## reference

https://skyul.tistory.com/68