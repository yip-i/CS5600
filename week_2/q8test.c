#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {
    int fd[2];

    if (pipe(fd) == -1) {
        printf("Error occured\n");
    }

    int pid = fork();
    if (pid < 0) {
        printf("fork error\n");
    }
    else if (pid == 0) {
        int x = 3;
        close(fd[0]);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    } else {
        int y;
        close(fd[1]);
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("Output: %d\n", y);
    }
}