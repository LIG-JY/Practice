#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *foo(void *)
{
	/*
	The pthread_self() function returns the ID of the calling thread.
	This is the same value that is returned in *thread in the pthread_create() call that created this thread.
	*/
	long thread_id = (long)pthread_self();

	printf("process id is %d\n", getpid());
	printf("thread id is %ld and call foo\n", thread_id);

	return NULL;
}

void *bar(void *)
{
	long thread_id = (long)pthread_self();

	printf("process id is %d\n", getpid());
	printf("thread id is %ld and call bar\n", thread_id);

	return NULL;
}

int main()
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t arr[3] = {thread1, thread2, thread3};

	for (int i = 0; i < 3; i++)
	{
		if (i % 2 == 0)
		{
			pthread_create(&arr[i], NULL, &foo, NULL);
		}
		else
		{
			pthread_create(&arr[i], NULL, &bar, NULL);
		}
		printf("thread %d's ", i + 1);
		pthread_join(arr[i], NULL); // thread의 실행이 완료될 때까지 호출한 thread가 대기하도록 만드는 함수
	}

	return 0;
}