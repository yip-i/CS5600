#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/*
Closing the STDOUT_FILENO means that the printing function no longer works.
However, the print function in the main program still works.
Interestingly, closing the stdout_fileno in the opening parts of the program pre-fork
disables printing for both the main and forked program.
*/

int main() {

    int status;
   

    int pid = fork();

    if (pid < 0) {
        return -1;
    } else if (pid == 0) {
        close(STDOUT_FILENO);

        printf("At child. PID: %d\n", getpid());
    } else {
        waitpid(pid, &status, 0);
        printf("status: %d\n", status);
        printf("At parent. PID: %d\n", getpid());
    }


    return 0;
}