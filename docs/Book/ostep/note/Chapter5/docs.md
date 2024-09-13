# Chapter 5

## fork()

### Why does the child process seem to “start” from the fork() call?

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("hello (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child (pid:%d)\n", (int)getpid());
    } else {
        // parent goes down this path (main)
        printf("parent of %d (pid:%d)\n", rc, (int)getpid());
    }
    return 0;
}

>> output
hello (pid:14795)
parent of 14798 (pid:14795)
child (pid:14798)
```

- fork()를 호출하면, 운영체제는 child process를 생성한다. child process는 parent process와 ***거의*** 동일하다.
- fork()는 호출 시점의 부모 process의 **현재 상태**를 복사한다.
    - 레지스터의 상태 (program counter)
    - 메모리의 상태 (address space)
- fork()를 호출 한 뒤 부모 process의 PC(program counter)는 if 문(line 16)의 명령어를 가리키게 됨
    - 따라서 자식 프로세스도 똑같이 line 16부터 순서대로 실행하게 됨
    - 그래서 마치 자식 프로세스도 fork()를 호출한 것 처럼 보이게 됨

- 부모 프로세스는 fork()의 반환값으로 자식 프로세스의 PID를 받게 됨 (rc == 14798) 따라서 else 문에 진입하게 됨
- 자식 프로세스는 fork()의 **반환값으로 0**을 받게됨.
    - UNIX에서 자식 프로세스는 fork()의 반환값을 0으로 주도록 설정함 (운영체제의 메커니즘)
    - 이를 통해서 부모와 자식 프로세스를 구분할 수 있음

- [fork()](https://man7.org/linux/man-pages/man2/fork.2.html)

> On success, the PID of the child process is returned in the
> parent, and 0 is returned in the child. On failure, -1 is
> returned in the parent, no child process is created, and errno is
> set to indicate the error.

## wait()

```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("child (pid:%d)\n", (int) getpid());
    } else { // parent goes down this path
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }
    return 0;
}
```

### Why pass NULL to wait()?

- 함수 시그니처는 다음과 같음 `pid_t wait(int *_Nullable wstatus);`
- 매개변수 wstatus는 자식 프로세스의 종료 상태 코드를 저장할 수 있는 포인터 변수
- NULL을 인자로 넘기면 자식 프로세스의 종료 상태를 저장하지 않음

- [wait()](https://man7.org/linux/man-pages/man2/waitpid.2.html)

### wait() return value

> wait(): on success, returns the process ID of the terminated
> child; on failure, -1 is returned.

## exec()

```shell
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());

    int rc = fork();

    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("child (pid:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("wc"); // program: "wc"
        myargs[1] = strdup("p3.c"); // arg: input file
        myargs[2] = NULL; // mark end of array
        execvp(myargs[0], myargs); // runs word count
        printf("this shouldn’t print out");
    } else { // parent goes down this path
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }
    return 0;
}
```

### Why doesn’t `printf()` Execute After `execvp()`?

- `execvp()` 함수는 현재 프로세스(자식 프로세스)의 주소 공간을 완전히 새로운 프로그램으로 덮어쓴다.
    - 여기서는 `execvp()`의 인자로 넘어온 wc(word count)
    - 메모리의 정적 데이터(코드 영역), 힙, 스택 등 모두 덮어씀
- fork()로 자식 프로세스가 생성되고, if문부터 순서대로 명령어를 실행한다. `execvp()`를 호출하면 새로운 프로그램으로 덮어쓰기 때문에 `printf()` 명령어는 메모리에서 지워짐
- 이는 [exec()](https://man7.org/linux/man-pages/man3/exec.3p.html) 시스템 콜 family의 공통적인 동작

> The exec family of functions shall replace the current process
> image with a new process image. The new image shall be
> constructed from a regular, executable file called the new
> process image file. There shall be no return from a successful
> exec, because the calling process image is overlaid by the new
> process image.

### fork vs exec

- fork는 자식 프로세스를 만들고 부모 프로세스의 상태를 복사
- exec는 새로운 프로램을 현재 프로세스에 덮어씀
    - 새로운 프로세스를 만들지 않음

## Internal behavior of the shell

```shell
prompt> wc p3.c > newfile.txt
```

1. parsing:
    - 쉘은 입력된 명령어 wc p3.c > newfile.txt를 파싱하여 실행할 프로그램(wc), 인자(p3.c), 그리고 출력 리다이렉션(> newfile.txt)을 식별
2. fork:
    - 쉘은 `fork()`를 사용하여 현재 프로세스(쉘)의 복사본인 자식 프로세스를 생성
3. 입출력 리다이렉션 설정:
    - 자식 프로세스에서 `exec()`를 호출하기 전 표준 출력을 닫고, 파일로 출력을 변경
    - 파일 디스크립터 1의 표준 출력을 닫고 파일을 열면 가장 낮은 사용 가능한 파일 디스크립터 번호가 할당됨, 이 때 1이 이미 닫혀있기 때문에 1이 할당
        - UNIX는 0 부터 free한 파일 디스크럽터를 검색함
4. exec:
    - 쉘은 `exec()`를 호출
    - 자식 프로세스의 메모리는 wc를 실행하도록 교체됨
    - 파일 디스크립터는 newfile.txt로 유지됨
5. 쉘에서 `wait()` 끝
    - 자식 프로세스의 작업이 끝나고, 쉘은 원래 상태로 돌아옴

### Why are file descriptors retained?

- exec() 함수는 현재 프로세스의 사용자 공간 메모리 영역을 새로운 프로그램으로 교체함
    - 여기에는 프로그램의 코드, 전역 변수, 힙, 스택 등이 포함됨
- 프로세스의 커널 레벨 상태는 그대로 유지됨
    - 파일 디스크립터는 여기에 포함
    - 파일 디스크립터는 프로세스가 열어놓은 파일, 소켓, 파이프 등에 대한 커널의 내부 참조. 이 참조는 메모리의 사용자 공간이 아니라 ***Kernal space***라는 독립적인 메모리에 보호됨
    - Kernal space에 저장되는 정보에 파일 디스크립터, PID, 프로세스(쉘)이 실행되는 디렉터리 등이 포함됨

## Pipe

```shell
grep -o foo file | wc -l
```

1. parsing
2. 파이프 생성
    - `pipe()` 시스템 콜로 파이프를 생성함
    - 파이프는 두개의 파일 디스크립터(write_end, read_end)로 구성됨,
        - Queue에서 rear, front 개념: 뒤(write_end)에 순서대로 데이터가 들어오고, 앞(read_end)에서 부터 읽고 큐에서 제거할 수 있음
    - 파이프는 단방향 프로세스간 통신을 위한 매커니즘(a unidirectional data channel that can be used for interprocess communication)
3. 프로세스 생 및 입출력 연결
    - 첫번째 프로세스(grep)
        - 쉘에서 `fork()`로 자식 프로세스 생성
        - 자식 프로세스의 표준 출력을 닫고 파이프의 write_end로 대체
        - 파일 디스크립터 1번이 write_end가 됨
    - 두번째 프로세스(wc)
        - fork
        - 자식 프로세스의 표준 입력을 닫고 파이프의 read_end로 대체
        - 파일 디스크립터 0번이 read_end가 됨
        - exec로 wc 실행, 입력을 read_end로 부터 받도록 설정
4. 각 프로세스 실행
    - 데이터는 grep에서 나와 wc에 들어가고 최종 결과는 쉘에 출력
    - 파이프라이닝

## Signal

[signal](https://en.wikipedia.org/wiki/Signal_(IPC)): UNIX 시스템에서 프로세스 간 통신을 위한 매커니즘

> Signals are standardized messages sent to a running program to trigger specific behavior, such as quitting or error
> handling. They are a limited form of inter-process communication (IPC)

- 시그널을 보내는 방법
    1. 쉘 단축키
        - Ex) Ctrl + C
    2. 쉘 명령어 `kill`
    3. 시스템 콜 `kill()`

- 프로세스에서 `signal()` 시스템 콜로 시그널에 대한 처리를 정의할 수 있음
    - 특정 시그널에 대한 핸들러 함수를 설정

- 일반 User은 자신이 소유한 프로세스에만 시그널을 보낼 수 있음
    - SuperUser은 모든 프로세스에 시그널을 보낼 수 있음. 시스템 관리자 권한
