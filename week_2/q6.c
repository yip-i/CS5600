#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


/*
Wait pid allows you to wait for a specific child rather than any child taht finishes.
This wuld be useful if you forked multiple times off of your main program and only cared to
wait for one of them.
http://poincare.matf.bg.ac.rs/~ivana/courses/ps/sistemi_knjige/pomocno/apue/APUE/0201433079/ch08lev1sec6.html

Waitpid also allows for a child's status to be fetched without blocking the main program.
*/

int main() {

    int status;
   

    int pid = fork();
    if (pid < 0) {
        return -1;
    } else if (pid == 0) {
        printf("At child. PID: %d\n", getpid());
    } else {
        waitpid(pid, &status, 0);
        printf("status: %d\n", status);
        printf("At parent. PID: %d\n", getpid());
    }


    return 0;
}