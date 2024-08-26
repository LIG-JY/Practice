# Determines if the given string is palindrome or not

## SOL1

```java
public static boolean isPalindromeV1(String s) {
    if (s.isBlank()) {
        return false;
    }

    StringBuilder sb = new StringBuilder(s);
    String reversed = sb.reverse().toString();

    return s.equals(reversed);
}

```

## SOL2

```java
public static boolean isPalindromeV2(String s) {

    if (s.isBlank()) {
        return false;
    }

    final int n = s.length() - 1;
    for (int i = (n - 1) >> 1; i >= 0; --i) {
        int j = n - i;
        if (s.charAt(i) != s.charAt(j)) {
            return false;
        }
    }

    return true;
}

```

## SOL3

```java
public static boolean isPalindromeV3(String s) {

    if (s.isBlank()) {
        return false;
    }

    int left = 0;
    int right = s.length() - 1;

    while (right > left) {

        if (s.charAt(left) != s.charAt(right)) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

```

## SOL4

```java
public static boolean isPalindromeV4(String s) {

    if (s.isBlank()) {
        return false;
    }

    int n = s.length();

    for (int i = 0; i < n / 2; i++) {
        if (s.charAt(i) != s.charAt(n - i - 1)) {
            return false;
        }
    }

    return true;
}

```

## SOL5

```java
public static boolean isPalindromeV5(String s) {

    if (s.isBlank()) {
        return false;
    }

    return IntStream.range(0, s.length() / 2).allMatch(i -> s.charAt(i) == s.charAt(s.length() - 1 - i));
}

```

## result

```shell
VER1
Execution time: 348792 ns (0 ms)
'ABCDEFEDCBA' is palindrome? true

VER2
Execution time: 8083 ns (0 ms)
'ABCDEFEDCBA' is palindrome? true

VER3
Execution time: 2291 ns (0 ms)
'ABCDEFEDCBA' is palindrome? true

VER4
Execution time: 2500 ns (0 ms)
'ABCDEFEDCBA' is palindrome? true
VER5
Execution time: 4232250 ns (4 ms)
'ABCDEFEDCBA' is palindrome? true
```

- Overhead in Object Creation:
    - object creation (as in VER1 with StringBuilder) introduces significant overhead
      because it involves allocating new memory and copying data, which is much more expensive than in-place operations
      like character comparison.

- Streams and Functional Operations:
    - Streams (VER5) introduce additional overhead due to their abstract nature, which
      involves creating
      intermediate objects and handling lambda expressions, resulting in much slower performance.

- Efficient Approaches:
    - The two-pointer approach (used in VER3 and VER4) is the most efficient because it directly
      compares the necessary characters without creating additional objects or performing unnecessary operations.
