# Typed Array

## What is `Typed Array`

- An array whose type information is maintained at runtime

## Array in JVM

- Arrays on the JVM cannot be created without knowing the element type
- In general, we cannot create an arbitrary array generically because generics are erased at
  runtime
    - this is `Type Erasure`
- Therefore,
  Kotlin [toArray()](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/-abstract-collection/to-array.html)
  does not
  know the type of the array, it returns Array<Any?> or creates an array by receiving an additional array argument.

## `Type Erasure` in JVM

- "Type erasure" can be explained as the process of enforcing type constraints only at compile time and discarding the
  element type information at runtime.

### reference

https://www.baeldung.com/java-type-erasure

## "reified" keyword

- Below is the implementation of
  the [toTypedArray()](https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/to-typed-array.html) function.
- toTypedArray() use `refied` keyword

```kotlin
@Suppress("UNCHECKED_CAST")
public actual inline fun <reified T> Collection<T>.toTypedArray(): Array<T> {
    @Suppress("PLATFORM_CLASS_MAPPED_TO_KOTLIN")
    val thisCollection = this as java.util.Collection<T>
    return thisCollection.toArray(arrayOfNulls<T>(0)) as Array<T>
}
```

- In Kotlin, we can use `reified` types that allow we to utilize type information at **compile time**.
    - This solves the problem of type information being erased at runtime
    - Allow to create arrays of more specific types.

- `reified` can only be used in inline functions.
    - Because inline functions are inserted at compile time at the location
      where the function body is called, the compiler is able to maintain specific information about the generic type.

## How `toTypedArray()` works?

- toArray() used in the return statement implements an abstract method `<T> T[] toArray(T[] a);`
- this abstract method copies all elements of this collection into the given array "a", and if the size of the array is
  not large enough, creates and returns a new array of the same type.
- arrayOfNulls<T>(0), which comes as an argument, creates an array with a length of 0, so the toArray method must create
  a new array.
- A new array is created as an array of type T, and the elements of the collection("thisCollection") are copied into the
  array and then
  returned.
- Casting to java.util.Collection<T>, calling the toArray function, and casting to Array<T> all occur during **RUNTIME
  **.
- In conclusion, `toTypedArray()` can maintain type information even during **RUNTIME
  **.

### reference

https://www.baeldung.com/java-collection-toarray-methods
