#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<errno.h>
// https://stackoverflow.com/questions/12300676/multiple-processes-write-to-the-same-file-c





int main(void) {

    mode_t mode = S_IRUSR | S_IWUSR;

    int filedesc = open("/Users/ianyip/Documents/Coding/CS5600/week_2/test", O_RDWR | O_CREAT, mode);
    printf("starting\n");

    //write(filedesc, "Test", 5);
    
    printf("filedesc: %d\n", filedesc);
    if (filedesc < 0) {
        printf("failure to open\n");
        return 1;
        
    }


    
    int rc = fork();

    if (rc < 0) {
        printf("fork failed\n");
        
    }
    if (rc == 0) {
        //printf("at fork filedesc: %d\n", filedesc);
        printf("at fork\n");
        if (write(filedesc, "hello world", 12) != 12) {
            printf("child write error\n");
            perror("write error");
            exit(1);
        }

    } else {
        wait(NULL);
        //printf("at parent filedesc: %d\n", filedesc);
        if (write(filedesc, "testing", 8) != 8) {
            printf("parent write error\n");

            perror("write error");
            exit(1);
        }
    }

    //close(filedesc);

    return 0;
}