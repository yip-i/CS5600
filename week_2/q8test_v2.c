#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>




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
        dup2(fd[1],STDOUT_FILENO);
        printf("%d", getpid());
        close(fd[1]);
    } else {
        int pid2 = fork();

        if (pid2 == 0) {
            close(fd[1]);

            int y;
            //read(fd[0], &y, sizeof(int));
            dup2(fd[0], STDIN_FILENO);
            scanf("%d", &y);

            close(fd[0]);

            printf("Current PID: %d, sibling PID: %d\n",getpid(), y);
        } else {
            close(fd[1]);
            close(fd[0]);
            printf("Parent PID: %d\n", getpid());
        }
    }
}