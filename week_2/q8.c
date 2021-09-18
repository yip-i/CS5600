#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main() {

    int fork1 = fork();
    int connection[2];

    if (pipe(connection) == -1) {
        printf("pipe failure\n");
        return -1;
    }

    if (fork1 < 0) {
        return -1;
    } else if (fork1 == 0) {
        //sleep(1);
        char input[] = "hello";

        close(connection[0]);
        write(connection[1], input, strlen(input) + 1);
        
        close(connection[1]);
        //printf("Input: %s", input);
        //printf("At child. PID: %d\n", getpid());
    } else {
        wait(NULL);
        close(connection[1]);

        int fork2 = fork();
        if (fork2 < 0) {
            return -1;
        } else if (fork2 == 0) {
            //printf("At child 2. PID: %d\n", getpid());
            char input_string[50];

            read(connection[0],input_string, 50);
            
            close(connection[0]);

            printf("Ouput: %s\n", input_string);
        }

    }
    return 0;

}