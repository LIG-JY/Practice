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
        printf("Child process executing /bin/ls using execl()\n");
        execl("/bin/ls", "ls", NULL);

        // If exec fails
        fprintf(stderr, "execl failed\n");
        exit(1);
    } else {
        // Parent process
        wait(NULL); // Wait for child to complete
        printf("Parent process: child has completed.\n");
    }

    return 0;
}