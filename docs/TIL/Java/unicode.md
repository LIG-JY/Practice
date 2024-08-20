# UNICODE

## From 16-Bit Encoding to Supplementary Characters

- `The Unicode standard` was initially designed using 16 bits to encode characters because the primary machines were
  16-bit PCs.
- When the specification for the Java language was created, `the Unicode standard` was accepted and the char primitive
  was
  defined as a 16-bit data type, with characters in the hexadecimal range from 0x0000 to 0xFFFF.
- `The Unicode standard` was extended to 0x10FFFF
- The characters with values that are outside the 16-bit range, and within the range from 0x10000 to 0x10FFFF, are
  called `supplementary characters` and are defined as a pair of char values.

## Supplementary Characters as Surrogates

- `supplementary characters` are defined by a pair of code point values that are called `surrogates`.
    - to support `supplementary characters` without changing the char primitive data type
- The first code point is from the `high surrogates` range of U+D800 to U+DBFF, and the second code point is
  from the `low surrogates` range of U+DC00 to U+DFFF.

## UTF-16

- The method using surrogate pairs is the core principle of UTF-16 encoding.
    - Code points in the range U+0000 to U+FFFF are represented in UTF-16 as a single 16-bit code unit
    - Code points in the range U+10000 to U+10FFFF are Converted from UTF-16 to a surrogate pair and expressed as two
      16-bit code units.
- For example, if U+10400 is encoded as UTF-16, it is as follows
    - Subtract 0x10000 from this character's code point (U+10400) and convert it to binary
        - 0x0400 ⇒ 0b0000010000000000
        - a single 16-bit code unit equal to the numerical value of the code point
    - Cut the bit pattern into 10 bits.
        - 0000000001/0000000000
        - The first 4 bits are filled with 0
    - High-Surrogate
        - 1101 1000 0000 0001
        - The first 10 bits can be replaced with x in `1101 10xx xxxx xxxx`
    - Low-Surrogate
        - 1101 1100 0000 0000
        - The second 10 bits can be replaced with y in `1101 11yy yyyy yyyy`
    - Convert each to a code point(16-bit code unit)
        - U+D801
        - U+DC00

```java
public static void main(String[] args) {
    var e = "\uD801\uDC00안녕";
    System.out.println(e.length()); // 4
    System.out.println(e.codePointCount(0, e.length()));    // 3
    System.out.println(Character.charCount(e.codePointAt(0)));  // 2
    System.out.println(Character.charCount(e.codePointAt(1)));  // 1
    System.out.println(Character.charCount(e.codePointAt(2)));  // 1
}
```

## reference

- https://docs.oracle.com/javase/tutorial/i18n/text/unicode.html
- https://en.wikipedia.org/wiki/UTF-16