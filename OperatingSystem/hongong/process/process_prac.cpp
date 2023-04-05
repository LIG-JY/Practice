#include <stdio.h>
#include <unistd.h>
/* getpid(), fork() -> unistd.h */

void foo()
{
	printf("execute foo\n");
}

void bar()
{
	printf("execute bar\n");
}

int main()
{
	printf("hello, os\n");
	printf("my pid is %d\n", getpid());

	// 자식 프로세스에게 fork() 의 return 은 0이다.
	if (fork() == 0)
	{
		if (fork() == 0)
		{
			// 18줄에서 생성된 Process
			printf("child of child pid is %d\n", getpid());
			bar();
		}
		else
		{
			// 17 줄에서 생성된 Process
			printf("child pid is %d\n", getpid());
			foo();
		}
	}
	else
	{
		if (fork() == 0)
		{
			// 28줄에서 생성된 Process
			printf("child pid is %d\n", getpid());
			foo();
		}
		// fork()의 return이 0이 아니면 자식 PID를 return 한다.
		else
		{
			printf("parent pid is %d\n", getpid());
		}
	}
	return 0;
}