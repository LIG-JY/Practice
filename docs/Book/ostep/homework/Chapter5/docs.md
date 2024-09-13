# Chapter 5

## 2) One control the simulator gives you is the fork percentage, controlled by the -f flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., -a 100) and vary the fork percentage from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes? Check your answer with -c.

```shell
$ python3 fork.py -s 10 -a 10 -f 0.1 -c

ARG seed 10
ARG fork_percentage 0.1
ARG actions 10
ARG action_list 
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b EXITS
                               a
Action: a forks c
                               a
                               └── c
Action: a forks d
                               a
                               ├── c
                               └── d
Action: c EXITS
                               a
                               └── d
Action: d EXITS
                               a
Action: a forks e
                               a
                               └── e
Action: a forks f
                               a
                               ├── e
                               └── f
Action: e EXITS
                               a
                               └── f
Action: f EXITS
                               a
```

```shell
$ python3 fork.py -s 10 -a 10 -f 0.9 -c

ARG seed 10
ARG fork_percentage 0.9
ARG actions 10
ARG action_list 
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c forks d
                               a
                               ├── b
                               └── c
                                   └── d
Action: a forks e
                               a
                               ├── b
                               ├── c
                               │   └── d
                               └── e
Action: b forks f
                               a
                               ├── b
                               │   └── f
                               ├── c
                               │   └── d
                               └── e
Action: f forks g
                               a
                               ├── b
                               │   └── f
                               │       └── g
                               ├── c
                               │   └── d
                               └── e
Action: e forks h
                               a
                               ├── b
                               │   └── f
                               │       └── g
                               ├── c
                               │   └── d
                               └── e
                                   └── h
Action: c forks i
                               a
                               ├── b
                               │   └── f
                               │       └── g
                               ├── c
                               │   ├── d
                               │   └── i
                               └── e
                                   └── h
Action: e forks j
                               a
                               ├── b
                               │   └── f
                               │       └── g
                               ├── c
                               │   ├── d
                               │   └── i
                               └── e
                                   ├── h
                                   └── j
Action: g forks k
                               a
                               ├── b
                               │   └── f
                               │       └── g
                               │           └── k
                               ├── c
                               │   ├── d
                               │   └── i
                               └── e
                                   ├── h
                                   └── j
```

- Low fork_percentage (e.g., 0.1): Since most of the behavior is exit, the tree will be narrow, shallow, and have many
  processes that exit quickly.

- High fork_percentage (e.g., 0.9): A lot of forks occur, so the tree is likely to be wide, with many child processes,
  resulting in a complex tree structure.

## 4) One interesting thing to note is what happens when a child exits; what happens to its children in the process tree? To study this, let’s create a specific example:`./fork.py -A a+b,b+c,c+d,c+e,c-`. This example has process ’a’ create ’b’, which in turn creates ’c’, which then creates ’d’ and ’e’. However, then, ’c’ exits. What do you think the process tree should like after the exit? What if you use the -R flag? Learn more about what happens to orphaned processes on your own to add more context.

```shell
$ python3 fork.py -A a+b,b+c,c+d,c+e,c- -c   

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               ├── b
                               ├── d
                               └── e
```

```shell
python3 fork.py -A a+b,b+c,c+d,c+e,c- -c -R

ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent True
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               └── b
                                   ├── d
                                   └── e
```

- On most Unix-like operating systems, when a parent process terminates, its children(orphaned) are re-parented as
  init processes (PID 1)
    - In this simulation init process's name is `a`.
    - In real, the init process is the first process to start when the system boots, with a PID of 1
- Some modern Linux systems introduce the concept of a ***subreaper***, which allows orphaned processes to be managed by
  a specific process.
    - [subreaper](https://unix.stackexchange.com/questions/250153/what-is-a-subreaper-process)
    - In this simulation `-R` flag is responsible for re-parenting children process to the closest living ancestor
      process when
      it becomes an orphan process 
