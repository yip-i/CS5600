#define _GNU_SOURCE

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
    
    cpu_set_t my_set;
    CPU_ZERO(&my_set);
    CPU_SET(7,&my_set);
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set);

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
        close(fd[0]);
        begin = start.tv_usec;

        write(fd[1], &begin, sizeof(double));
        close(fd[1]);
        return 0;
    } else {

        wait(NULL);
        gettimeofday(&stop, NULL);

        close(fd[1]);
        read(fd[0], &begin, sizeof(double));
        close(fd[0]);
        difference = (stop.tv_usec - begin) * 100;
        printf("Time: %f\n", difference);

    }



}