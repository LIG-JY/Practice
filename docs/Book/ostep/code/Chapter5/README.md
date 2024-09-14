# Chapter 5 homework(code)

## 1)

[code](1.c)

### output

```shell
Chile process pid: 91661
Parent process before change, x = 100
Parent process after change, x = 300
Child process before change, x = 100
Child process after change, x = 200
```

The order of output may vary from run to run

### Independent Memory Space

When fork() is called, it creates a child process that is a copy of the parent process.
However, after the fork(), the parent and child processes have independent memory spaces. Changes to variables in one
process do not affect the other, as they operate on separate copies of the memory.

### Non-deterministic Execution Order

After a fork(), both the parent and child processes execute concurrently. The order in which they run is
non-deterministic, meaning the operating system’s scheduler decides which process runs first, and the sequence may vary
with each execution.

## 2)

[code](2.c)

### output

example.txt

```shell
Parent process writing to file.
Parent process writing to file.
Parent process writing to file.
Parent process writing to file.
Parent process writing to file.
Child process writing to file.
Child process writing to file.
Child process writing to file.
Child process writing to file.
Child process writing to file.
```

if commenting out `wait()` race condition occur.

```
Child process writing to file.
Parent process writing to file.
Parent process writing to file.
Child process writing to file.
Child process writing to filParent process writing to file.
Parent process writing to filChild process writing to file.
...
```

### How the Kernel Manages File Descriptors

File descriptors are integral components of an operating system’s kernel, designed to handle open files and other I/O
resources. When a process opens a file, the kernel allocates a file descriptor, which is a small integer that acts as an
***index*** to the file’s entry in the kernel’s ***file table***. This table contains important metadata about the file,
such as the
file offset, access permissions, and the current state of the file. File descriptors are exclusive to the kernel’s
space, allowing the kernel to manage multiple files and resources efficiently while abstracting this complexity from the
user process.

### How Processes Use File Descriptors and Behavior with fork()

When a process opens a file, it receives a file descriptor from the kernel, which it uses to interact with the file via
system calls like `read()`, `write()`, and `close()`. The file descriptor itself is just a number that the user process
holds
in its ***own memory space***, acting as a key for accessing the underlying kernel-managed file information.

When fork() is invoked, the child process is created as a near-identical copy of the parent process, including its
memory space and file descriptor table. Although the child and parent have independent copies of the file descriptor (
each stored in their own process memory), these descriptors point to the ***same*** kernel-managed file table entry. As
a
result, both processes share access to the same open file, and changes to the file offset or other state variables are
visible to both.

### Race Condition Due to Shared File Descriptors

Given that both the parent and child processes share access to the same file descriptor entry in the kernel after
fork(), concurrent access to the file can lead to race conditions. If both processes attempt to write to the file
simultaneously, they will be competing for access to the shared file offset. This can result in interleaved writes,
where the output from the two processes overlaps unpredictably. This race condition is further influenced by CPU
scheduling, as the operating system determines when each process gains access to the CPU. Without synchronization
mechanisms, the outcome of such concurrent writes is non-deterministic and can lead to data corruption or loss, with
file contents potentially being overwritten or interleaved in unintended ways.

## 3)

[code](3.c)
[read](https://man7.org/linux/man-pages/man2/read.2.html)
[write](https://man7.org/linux/man-pages/man2/write.2.html)
[pipe](https://man7.org/linux/man-pages/man2/pipe.2.html)

The blocking I/O characteristic of pipes can be used to control the execution order of processes.

### output

```shell
hello
child process done
goodbye
```

### The Role of the `pipe()` Function

The pipe() function creates a ***memory-based*** pipe for inter-process communication without generating a file.
When pipe() is successfully called, it returns two file descriptors:

- pipe_fd[0]: A read-only file descriptor.
- pipe_fd[1]: A write-only file descriptor.

This enables two processes to establish a communication channel that allows data transfer in memory.

### How a Pipe Works

A pipe operates in a ***blocking I/O*** mode and follows a ***FIFO*** (First In, First Out) structure.

#### Blocking I/O

**Write operation**: When writing data to the pipe, if the buffer is full, the write operation blocks until space
becomes
available. If space exists, data is written immediately.

**Read operation**: If no data is present in the pipe, the read operation blocks and waits. It will remain in a waiting
state until data is written to the pipe.

This blocking behavior can be leveraged to enforce execution order between processes. For example, a parent process
can be made to wait until the child process writes data to the pipe, ensuring sequential execution.

#### FIFO

The pipe processes data in a FIFO manner: Once data is written, it accumulates in the kernel buffer, and when it is
read, it is removed from the buffer.

#### Kernel buffer

The size of the kernel buffer depends on the platform and kernel version, but it is typically around 64KB. Once the
buffer is full, the write operation blocks until the buffer is cleared by a read operation.

### File Descriptors and Pipes

In Unix-like operating systems, everything is treated as a file, a concept known as ***Everything is a file***. This
includes pipes.

A file descriptor is an **interface** that allows a process to access kernel-managed resources (such as files, sockets,
or
pipes). A pipe provides unidirectional communication between processes, with separate file descriptors for reading and
writing.

## 4)

[code](4.c)

[exec family](https://man7.org/linux/man-pages/man3/exec.3.html)

There are many variants of exec() to provide flexibility in how a new program is executed. (depending on the use case)

## 5)

[wait() return value](https://man7.org/linux/man-pages/man2/waitpid.2.html#RETURN_VALUE)

> wait(): on success, returns the process ID of the terminated
> child; on failure, -1 is returned.

If a child process calls `wait()`, it will try to wait for its own children. However, if the child process has not
created
any children, it has nothing to wait for, so `wait()` will fail and return -1, with an **ECHILD** error set in errno.

> ECHILD (for wait()) The calling process does not have any
> unwaited-for children.

## 6)

[waitpid()'s arguments](https://man7.org/linux/man-pages/man2/waitpid.2.html#DESCRIPTION)

Wait for a specific child process by passing its PID as an argument. Provide finer control with options, such as
non-blocking behavior (e.g., WNOHANG)

## 7)

[code](7.c)

### output

```shell
Child: Closing STDOUT_FILENO
Parent: Child process finished
```

[close](https://man7.org/linux/man-pages/man2/close.2.html)

### `close()`s behavior

The `close()` function removes the file descriptor from the ***file descriptor table*** of the calling process. The
kernel also
decrements the ***reference count*** for the file, and when the count reaches zero, the kernel releases the associated
resources.

### `fork()` and file descriptor

Each process manipulates its own independent file descriptor table, and closing a file descriptor in one process does
not affect other processes. This is because `fork()` creates a separate memory space for the child process, including a
copy of the parent’s file descriptors.

## 8)

[code](8.c)

[dup()](https://man7.org/linux/man-pages/man2/dup.2.html)

> The dup2() system call performs the same task as dup(), but
> instead of using the lowest-numbered unused file descriptor, it
> uses the file descriptor number specified in newfd. In other
> words, the file descriptor newfd is adjusted so that it now
> refers to the same open file description as oldfd.