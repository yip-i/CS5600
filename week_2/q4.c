#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
Tested the different versions of exec.
Reading this page: https://man7.org/linux/man-pages/man3/exec.3.html
Some of the commands appear to reference files and also have different inputs.
Could be calling different parts of the system.

Here is another article I found https://stackoverflow.com/questions/5769734/what-are-the-different-versions-of-exec-used-for-in-c-and-c.
This one explains that there are different ways of passing arguments to be executed.
Program doesn't appear to end without a wait on the parent.
*/
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