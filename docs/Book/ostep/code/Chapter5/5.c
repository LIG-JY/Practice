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
        printf("Child process started\n");
        int status; // wstatus
        pid_t wpid = wait(&status);  // parent waits for child to finish
        if (wpid == -1) {
            perror("wait failed");
        } else {
            printf("Child process waited for child (PID: %d)\n", wpid);
        }
        printf("Child process finished\n");
        exit(0);  // terminate child process
    } else {
        // Parent process
        int status; // wstatus
        pid_t wpid = wait(&status);  // parent waits for child to finish
        if (wpid == -1) {
            perror("wait failed");
        } else {
            printf("Parent process waited for child (PID: %d)\n", wpid);
        }

        // this macro returns true if the child exited normally
        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}