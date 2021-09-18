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
#include <sched.h>


int main(int argc, char* argv[]) {
    
    CPU_ZERO(&my_set);

    struct timeval start,stop;
    double difference;
    double begin, end;

    int pid = fork();
    int fd[2];
    if (pipe(fd) == -1) {
        printf("Pipe error\n");
    }

    if (pid < 0) {
        printf("Error\n");
    } else if (pid == 0) {

        gettimeofday(&start, NULL);
        begin = start.tv_usec;
        close(fd[0]);
        write(fd[1], &begin, sizeof(double));
        close(fd[1]);
    } else {
        close(fd[1]);
        read(fd[0], &begin, sizeof(double));
        close(fd[0]);
        gettimeofday(&stop, NULL);
        difference = (stop.tv_usec - begin) * 100;
        printf("Time: %f\n", difference);

    }



}