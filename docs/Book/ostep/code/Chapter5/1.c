#include <stdio.h>
#include <unistd.h>  // for fork()
#include <stdlib.h> // for exit()

int main(int argc, char* argv[])
{
    int x = 100;

    pid_t pid = fork();

    if (pid < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid == 0) { // child (new process)
        // Child process
        printf("Child process before change, x = %d\n", x);
        x = 200;  // Change value of x in child
        printf("Child process after change, x = %d\n", x);
    } else { // parent goes down this path
        // Parent process
        printf("Chile process pid: %d\n", pid);
        printf("Parent process before change, x = %d\n", x);
        x = 300;  // Change value of x in parent
        printf("Parent process after change, x = %d\n", x);
    }
    return 0;
}