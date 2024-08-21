# Reverse word in sentence

- Reverse each token in a string

## SOL1

```java
public static String reverseWords(String str) {
    String[] words = str.split(" ");
    StringBuilder sb = new StringBuilder(str.length());

    for (int i = 0; i < words.length; i++) {
        String word = words[i];
        char[] newWord = word.toCharArray();
        int j = 0;
        int k = word.length() - 1;
        while (j < k) {
            char temp = newWord[j];
            newWord[j] = newWord[k];
            newWord[k] = temp;
            ++j;
            --k;
        }
        sb.append(newWord);
        if (i < words.length - 1) {
            sb.append(' ');
        }
    }

    return sb.toString();
}
```

## SOL2

```java
public static String reverseWords(String str) {
    String[] words = str.split(" ");
    StringBuilder sb = new StringBuilder(str.length());

    for (int i = 0; i < words.length; i++) {
        sb.append(new StringBuilder(words[i]).reverse());
        if (i < words.length - 1) {
            sb.append(' ');
        }
    }

    return sb.toString();
}
```

- the reverse() function traverses only half of the array

```java
public AbstractStringBuilder reverse() {
    byte[] val = this.value;
    int count = this.count;
    int n = count - 1;
    if (isLatin1()) {
        for (int j = (n - 1) >> 1; j >= 0; j--) {
            int k = n - j;
            byte cj = val[j];
            val[j] = val[k];
            val[k] = cj;
        }
    } else {
        StringUTF16.reverse(val, count);
    }
    return this;
}
```

### reference

- https://docs.oracle.com/javase/8/docs/api/java/lang/StringBuilder.html#reverse--

## SOL3

```java
public static String reverseWordsV2(String str) {
    return Pattern.compile(" +").splitAsStream(str)
            .map(w -> new StringBuilder(w).reverse())
            .collect(Collectors.joining(" "));
}
```

- `+`: This metacharacter means that the preceding expression is repeated one or more times
- so pattern ` +`  means one or more whitespaces

### reference

- https://docs.oracle.com/javase/8/docs/api/java/util/regex/Pattern.html#splitAsStream-java.lang.CharSequence-