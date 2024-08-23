# Generates all permutations of a given string

## SOL1

```java
public static Set<String> permuteAndStore(String str) {

    if (str == null || str.isBlank()) {
        return Collections.emptySet();
    }

    return permuteAndStore(new StringBuilder(str.length()), str);
}

private static Set<String> permuteAndStore(StringBuilder output, String str) {

    Set<String> result = new HashSet<>();

    int length = str.length();
    if (length == 0) {
        result.add(output.toString());
    } else {
        for (int i = 0; i < length; i++) {
            output.append(str.charAt(i));
            result.addAll(permuteAndStore(new StringBuilder(output), str.substring(0, i) + str.substring(i + 1)));
            output.deleteCharAt(output.length() - 1);
        }
    }

    return result;
}
```

## SOL2

```java
public static Stream<String> permuteAndReturnStream(String str) {

    if (str == null || str.isBlank()) {
        return Stream.of("");
    }

    return IntStream.range(0, str.length())
            .parallel()
            .boxed()
            .flatMap(i -> permuteAndReturnStream(str.substring(0, i) + str.substring(i + 1)).map(s -> str.charAt(i) + s));
}
```

### why use boxed?

- Intstream does not provide flatmap(), which returns Stream<String>.
- Stream<T> (reference type stream) provide flatmap which can return Stream<String>

```java
IntStream flatMap(IntFunction<? extends IntStream> mapper);
```