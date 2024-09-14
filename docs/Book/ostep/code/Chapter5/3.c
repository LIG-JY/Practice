#include <stdio.h>
#include <unistd.h>  // for fork(), for close(), write(), and other system calls
#include <stdlib.h> // for exit()
#include <fcntl.h>  // for open()

int main(int argc, char* argv[])
{
    int pipe_fd[2]; // for pipe
    if (pipe(pipe_fd) == -1) {  // create pipe
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (pid == 0) {
        // Child process
        close(pipe_fd[0]);  // close read end file descriptor
        write(pipe_fd[1], "done", 5);   // write data to write end
        printf("hello\n");
        close(pipe_fd[1]);   // close write end file descriptor
    } else {
        // Parent Process
        char buffer[5];
        close(pipe_fd[1]);   // close write end file descriptor
        read(pipe_fd[0], buffer, 5);    // read data from read end, process wait until data is written to the pipe.
        printf("child process %s\n", buffer);
        printf("goodbye\n");
        close(pipe_fd[0]);  // close read end file descriptor
    }

    return 0;
}