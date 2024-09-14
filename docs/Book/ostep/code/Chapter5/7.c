#include <stdio.h>
#include <unistd.h>  // for fork(), for close(), write(), and other system calls
#include <stdlib.h> // for exit()
#include <fcntl.h>  // for open()

int main(int argc, char* argv[])
{
    pid_t pid = fork();

    if (pid < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (pid == 0) {
        // Child process
        printf("Child: Closing STDOUT_FILENO\n");
        close(STDOUT_FILENO);  // file descriptor of stdout == 1
        printf("Child: You should not see this message!\n");
    } else {
        // Parent process
        wait(NULL); // wait for child process to be terminated
        printf("Parent: Child process finished\n");
    }

    return 0;
}