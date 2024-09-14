#include <stdio.h>
#include <unistd.h>  // for fork(), for close(), write(), and other system calls
#include <stdlib.h> // for exit()
#include <fcntl.h>  // for open()

int main(int argc, char* argv[])
{
    int pipe_fd[2];  // File descriptors for the pipe
    if (pipe(pipe_fd) == -1) {  // Create the pipe
        perror("pipe failed");
        exit(1);
    }

    pid_t pid1 = fork();  // Create the first child process
    if (pid1 < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        // First child process (sends data through the pipe)
        close(pipe_fd[0]);  // Close the read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);  // Redirect standard output to the write end of the pipe

        char message[] = "Hello from child process 1\n";
        write(STDOUT_FILENO, message, sizeof(message) - 1); // Send message to pipe(STDOUT)

        close(pipe_fd[1]);  // Close the write end of the pipe (no longer needed)
    }

    pid_t pid2 = fork();  // Create the second child process
    if (pid2 < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid2 == 0) {
        // Second child process (receives data from the pipe)
        close(pipe_fd[1]);  // Close the write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);  // Redirect standard input to the read end of the pipe

        char buffer[128];
        size_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);  // Read message from pipe
        buffer[bytes_read] = '\0';  // Null-terminate the string
        printf("Child process 2 received: %s", buffer);

        close(pipe_fd[0]);  // Close the read end of the pipe (no longer needed)
    }

    // Parent process
    close(pipe_fd[0]);  // Parent closes the read end of the pipe
    close(pipe_fd[1]);  // Parent closes the write end of the pipe

    // Wait for both child processes to finish
    wait(NULL);  // Wait for the first child process to finish
    wait(NULL);  // Wait for the second child process to finish

    return 0;
}