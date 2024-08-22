# Partition the characters of a string into consonants and vowels

## SOL

```java
public class StringUtil {

    public static Long getLowerVowelCount(String word) {
        var res = partitioningCharacters(word);

        return res.getOrDefault(true, 0L);
    }

    private static Map<Boolean, Long> partitioningCharacters(String str) {
        Set<Character> allVowels
                = new HashSet<>(Arrays.asList('a', 'e', 'i', 'o', 'u'));

        str = str.toLowerCase();

        return str.chars()
                .mapToObj(c -> (char) c)
                .filter(ch -> (ch >= 'a' && ch <= 'z'))
                .collect(partitioningBy(allVowels::contains, counting()));
    }
}
```

### reference

- https://docs.oracle.com/javase/8/docs/api/java/util/stream/Collectors.html#partitioningBy-java.util.function.Predicate-
