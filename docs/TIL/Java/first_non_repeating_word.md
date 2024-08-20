# Find first non-repeating word in string

## SOL1

```java
public static Character getFirstNonRepeatingCharOrNUll(String str) {
    int[] map = new int[ASCII]; // stores an index of non-repeating characters
    Arrays.fill(map, -1);

    for (int i = 0; i < str.length(); i++) {
        char ch = str.charAt(i);
        if (map[ch] == -1) {  // The first non-repeating character
            map[ch] = i;
        } else {    // repeating character
            map[ch] = -2;
        }
    }

    int position = str.length();

    for (int index : map) {
        if (index >= 0 && index < position) {
            position = index;
        }
    }

    return position == str.length() ? null : str.charAt(position);
}
```

## SOL2

```java
public static Character getFirstNonRepeatingCharOrNUll(String str) {
    Map<Character, Integer> map = new LinkedHashMap<>(ASCII);

    for (char c : str.toCharArray()) {
        map.compute(c, (k, v) -> v == null ? 1 : ++v);
    }

    for (var e : map.entrySet()) {
        if (e.getValue() == 1) {
            return e.getKey();
        }
    }

    return null;
}
```

- **linked hash map** maintain order and define ordering
    - insertion order

### reference

https://docs.oracle.com/javase/8/docs/api/java/util/LinkedHashMap.html

## SOL3

```java
public static Character getFirstNonRepeatingCharOrNUll(String str) {
    Map<Character, Long> map = str.chars().mapToObj(ch -> (char) ch)
            .collect(Collectors.groupingBy(c -> c, Collectors.counting()));

    return map.entrySet().stream()
            .filter(entry -> entry.getValue() == 1L)
            .findFirst()
            .map(Map.Entry::getKey)
            .orElse(null);
}
```

### groupingBy()

```java
public static <T, K, A, D>
Collector<T, ?, Map<K, D>> groupingBy(Function<? super T, ? extends K> classifier,
                                      Collector<? super T, A, D> downstream) {
    return groupingBy(classifier, HashMap::new, downstream);
}
```

- Returns a Collector implementing a cascaded "group by" operation on input elements of type T, grouping elements
  according to a **classification function**, and then performing a reduction operation on the values associated with a
  given key using the specified **downstream Collector**.

- param1
    - Function<? super T, ? extends K>
    - `c -> c`
        - This lambda function returns input elements as is
        - T: Character, K: Character
    - Input element itself becomes the key
- param2
    - Collector<? super T, A, D> downstream
    - `Collectors.counting()`
  ```java
    public static <T> Collector<T, ?, Long>
    counting() {
        return summingLong(e -> 1L);
    }
    ```
    - T: Character, D: Long
    - The downstream collector calculates a Long type value for each grouped element and returns it as D
    - This is **downstream reduction**

### refrence

https://docs.oracle.com/javase/8/docs/api/java/util/stream/Collectors.html#groupingBy-java.util.function.Function-java.util.stream.Collector-
