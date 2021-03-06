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
    long difference;

    int pid = fork();
    int fd[2];
    if (pipe(fd) == -1) {
        printf("Pipe error\n");
    }

    if (pid < 0) {
        printf("Error\n");
    } else if (pid == 0) {
        long begin;
        gettimeofday(&start, NULL);
        close(fd[0]);
        begin = start.tv_sec;

        write(fd[1], &begin, sizeof(long));
        close(fd[1]);
        printf("fork begin: %ld\n", begin);

    } else {
        wait(NULL);
        gettimeofday(&stop, NULL);
        long end;
        close(fd[1]);
        read(fd[0], &end, sizeof(long));
        close(fd[0]);
        difference = (stop.tv_sec - end);
        printf("Main begin: %ld\n", end);
        printf("stop: %ld\n", stop.tv_sec);
        //printf("%d")
        printf("Time: %ld\n", difference);

    }



}