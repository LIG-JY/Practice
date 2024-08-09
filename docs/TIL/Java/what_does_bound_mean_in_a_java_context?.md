# Bound

## What does `bound` mean in a java context

- The term `bound` refers to a constraint or restriction placed on the type parameter E(generic)
- This concept is commonly known as `bounded type parameters` in Java generics
    - Specifically, it means that the type parameter E is restricted to be a subtype of a particular type or set of
      types
- Below is an example, the type parameter E is bound by the interface Comparable<E>, which means that any type E
  used with this generic class must implement the Comparable<E> interface.

```java
public class Example<E extends Comparable<E>> {
    // class implementation
}
```

## Bounded Type Parameters

- In Java generics, you can restrict the types that can be used as arguments for a type parameter. This is done using
  the `extends` keyword for upper bounds (limiting to subclasses or subinterfaces) or `super` for lower bounds (limiting
  to
  superclasses or superinterfaces).

## Compiler’s Interpretation

- The Java compiler uses the bound (in this case upper bound, Comparable<E>) to ensure **type safety**. If E is replaced
  with a raw type
  due to **type erasure** (the process where generic type information is removed during compilation), it will be treated
  as
  the `first bound` in the bound list, which is Comparable here. Hence, in the erased version of the class, E is
  replaced
  with Comparable.

### First bound

- The bound which is closest to the type parameter E
- In Java generics, if you specify multiple bounds for a type parameter, the first one listed is considered the primary
  or "first" bound

```java
public class MultiBoundClass<E extends Comparable<E> & Serializable & Cloneable> {
    // class implementation
}
```

1. Comparable<E>: The first bound (primary bound)
2. Serializable: The second bound
3. Cloneable: The third bound

## Multiple Bounds

- A type variable with multiple bounds is a subtype of all the types listed in the bound.
    - If one of the bounds is a class, it must be specified first(primary)

```java
Class A { /* ... */ }
interface B { /* ... */ }
interface C { /* ... */ }

class D <T extends A & B & C> { /* ... */ }
```

- If bound A is not specified first, you get a compile-time error

```java
class D <T extends B & A & C> { /* ... */ }  // compile-time error
```

## reference

https://docs.oracle.com/javase/tutorial/java/generics/bounded.html
https://docs.oracle.com/javase/specs/jls/se8/html/jls-4.html#jls-4.6
