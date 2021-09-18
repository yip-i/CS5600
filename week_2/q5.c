#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


/*
Saw a use of wait null online and was curious for what it did.
https://stackoverflow.com/questions/42426816/how-does-waitnull-exactly-work#:~:text=1%20Answer&text=wait(NULL)%20will%20block%20parent,of%20its%20children%20has%20finished.&text=In%20other%20words%3A%20parent%20process,then%20returned%20to%20parent%20process.
Apparently a parent know when it has a child and a wait(null) allows parent to wait.

wait returns the process ID of the child.

Putting wait in the child appears to make the parent always run first.
Although pretty sure that is a coincedence.
Wait waits for any child to finish.

*/


int main() {

   

    int pid = fork();
    if (pid < 0) {
        return -1;
    } else if (pid == 0) {
        printf("Wait %d\n",wait(NULL));
        printf("At child. PID: %d\n", getpid());
    } else {
        //int wait_return = wait(NULL);
        //printf("Wait: %d\n", wait_return);
        printf("At parent. PID: %d\n", getpid());
    }


    return 0;
}