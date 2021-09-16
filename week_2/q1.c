#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void) {
    int x = 100;

    printf("Start value of x: %d\n", x);

    int rc = fork();

    if (rc <0) {
        // fork failed
        printf("fork failed\n");
    } else if (rc == 0) {
        x += 5;
        printf("number at child: %d\n", x);
    } else {
        // Parent
        wait(NULL);
        x -= 1;
        printf("number at parent: %d\n", x);
    }
    printf("final value of x: %d\n", x);

    return 0;
}