#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {

    char *myargs[2];
    myargs[0] = strdup("/bin/ls");

    myargs[1] = NULL;

    int pid = fork();
    if (pid < 0) {
        return -1;
    } else if (pid == 0) {
        execvp(myargs[0], myargs);
    } else {
        wait(NULL);
        printf("parent\n");
    }


    return 0;
}