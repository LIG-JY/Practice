# Check that string contains only digits

## SOL1

```java
 public static boolean containsOnlyDigits(String str) {
    return str.chars().allMatch(Character::isDigit);
}

public static boolean containsOnlyDigitsV2(String str) {
    return !str.chars().anyMatch(c -> !Character.isDigit(c));
}
```

- anyMatch(), allMatch() accepts an argument of type IntPredicate, which is a functional interface that represents a
  predicate (a boolean-valued function) for an int value
- When the Java runtime invokes method containsOnlyDigits(), it is expecting a data type predicate for an int value
    - The data type that method expects is called the **target type**
- To determine the type of a lambda expression, the Java compiler uses the **target type** of the context or situation in
  which the lambda expression was found. (COMPILE TIME inference)

### reference

- https://docs.oracle.com/javase/tutorial/java/javaOO/lambdaexpressions.html#target-typing

## SOL2

```java
public static boolean containsOnlyDigits(String str) {
    for (char c : str.toCharArray()) {
        if (!Character.isDigit(c)) {
            return false;
        }
    }

    return true;
}
```
