#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include<errno.h>


int main(int argc, char* argv[]) {
    struct timeval start,stop;
    long difference;

    gettimeofday(&start, NULL);
    int filedesc = open("/Users/ianyip/Documents/Coding/CS5600/week_2/test", O_RDWR | O_CREAT, 0000);
    close(filedesc);
    gettimeofday(&stop, NULL);
    difference = (stop.tv_usec - start.tv_usec) * 100;
    printf("difference: %ld\n", difference);
}