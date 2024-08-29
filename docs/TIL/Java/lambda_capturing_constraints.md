# Lambda Capturing in Java: Constraints and Behavior

## Lambda Capturing Constraints in Java

- When working with lambda expressions in Java, a significant constraint is that they can only capture
  ***effectively final*** local variables.
    - This means that the local variables captured by a lambda expression must not be modified after being
      assigned.
- On the other hand, instance variables and static variables do not face this restriction, allowing them to be
  freely accessed and modified within lambda expressions.

- This distinction arises from how these variables are stored
  and managed by the JVM during execution.

## Understanding the JVM: Memory Allocation and Variable Constraints

- The Java Virtual Machine (JVM) enforces these constraints based on its memory management model.
- Local variables are stored on the stack, which is thread-specific and has a limited lifetime tied to the method’s
  execution.
    - The limitation on capturing local variables in lambdas exists because the
      lambda expression may outlive the stack frame where the local variable was declared, leading to potential access
      of invalid memory locations.
- Instance variables are stored on the heap, and static variables in the method area(or heap), both of which have a
  longer lifecycle and are shared across threads.

### JVM Storage for Static Members

- Before java8: PermGen
- After java8: heap

### reference

- https://www.baeldung.com/jvm-static-storage
- https://www.baeldung.com/java-permgen-metaspace

## How Lambda Capturing Works in Java

- Lambda expressions are syntactic sugar that the compiler transforms into anonymous inner classes.
- The JVM handles lambda capturing by copying the values of local variables (if they are effectively final) into a
  ***synthetic field*** of the generated class.
    - This means that anonymous class objects are allocated on the heap, and synthetic fields are also stored on the
      heap
    - When lambda capturing work, instead of accessing a local variable on the short-lived stack, it accesses a copy of
      the local variable as a synthetic field on the heap.

### Synthetic Field

- A synthetic field is a field that is automatically created by the Java compiler during the translation of certain code
  constructs into bytecode. It is not directly declared in the source code by the programmer but is generated to
  facilitate certain language features, such as lambda expressions, inner classes, or when anonymous classes are
  created.
- Synthetic fields are used ***to store references to local variables***, outer class instances, or other necessary
  values that are needed for the correct functioning of these constructs at runtime.
