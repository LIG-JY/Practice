#include <stdio.h>
#include <unistd.h>  // for fork(), for close(), write(), and other system calls
#include <stdlib.h> // for exit()
#include <fcntl.h>  // for open()

int main(int argc, char* argv[])
{
    int fd = open("example.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd < 0) {
        perror("Failed to open file");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (pid == 0) {
        // Child process
        const char* child_msg = "Child process writing to file.\n";
        for (int i = 0; i < 5; i++) {
            write(fd, child_msg, sizeof("Child process writing to file.\n") - 1);
        }
    } else {
        // Parent Process
        const char* parent_msg = "Parent process writing to file.\n";
        for (int i = 0; i < 5; i++) {
            write(fd, parent_msg, sizeof("Parent process writing to file.\n") - 1);
        }
        wait(NULL); // To clearly identify race condition, comment out this code.
    }
    close(fd);

    return 0;
}