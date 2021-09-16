#include <stdio.h>

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
        
        printf("Hello\n");
    } else {
        sleep(1);
        printf("Goodbye\n");
    }

    return 0;
}