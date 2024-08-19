# How to count characters in a String

## SOL1

```java
public static Map<Character, Long> getCharCount(String str) {
        Map<Character, Long> map = new HashMap<>();

        for (char c : str.toCharArray()) {
            map.compute(c, (k, v) -> v == null ? 1 : ++v);
        }

        return map;
    }
```

### reference

https://docs.oracle.com/javase/8/docs/api/java/util/Map.html#compute-K-java.util.function.BiFunction-

## SOL2

```java
public static Map<Character, Long> getCharCount(String str) {
        return str.chars()
                .mapToObj(ascii -> (char) ascii)
                .collect(Collectors.groupingBy(c -> c, Collectors.counting()));
    }
```

### Explanation

#### collect()
- collect() method perform `mutable reduction` operation. Therefore, the result is a mutable container.
- collect() method receives `Collector` as an argument.
- `concurrent reduction` will be performed if the following conditions are met.
    - condition 1
        - stream runs in parallel using multiple threads
    - condition 2
        - the `Collector` is concurrent.
        - Therefore, it is safe even if multiple threads access it simultaneously.
    - condition 3
        - either the stream is unordered or the collector is unordered.
        - That is, when the order of elements is not important.
- `concurrent reduction` is done by having each thread perform work independently and then merge the results.
- collect() method is a `termianl operation`
    - Stream Termination:
        - When a terminal operation is called, it terminates the stream, meaning no more intermediate
          operations can be added.
        - The stream is **consumed** and cannot be reused.
        - If we need to traverse the same data source again, we must return to the data source to get a new stream
    - Result Production:
        - Terminal operations typically produce a result.
        - This result could be a collection, an array, a primitive value, or some other outcome.
    - Eager Execution:
        - `intermediate operations` are lazily evaluated (i.e., they are not executed until a terminal
          operation is invoked), terminal operations trigger the execution of the entire stream pipeline.
        - All intermediate operations are executed when the terminal operation is called.

### reference

https://docs.oracle.com/en%2Fjava%2Fjavase%2F11%2Fdocs%2Fapi%2F%2F/java.base/java/util/stream/Stream.html#collect(java.util.stream.Collector)