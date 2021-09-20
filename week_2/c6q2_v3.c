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
    int fd[2];
    struct timeval start,stop, other_start;
    cpu_set_t my_set;
    CPU_ZERO(&my_set);
    CPU_SET(7,&my_set);
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set);


    if (pipe(fd) == -1) {
        printf("Error occured\n");
    }

    int pid = fork();
    if (pid < 0) {
        printf("fork error\n");
    }
    else if (pid == 0) {
        close(fd[0]);

        gettimeofday(&start,NULL);

        long x = start.tv_usec;
        write(fd[1], &start, sizeof(struct timeval));
        close(fd[1]);
        return 0;
    } else {
        wait(NULL);
        gettimeofday(&stop, NULL);
        long y;
        close(fd[1]);
        read(fd[0], &other_start, sizeof(struct timeval));
        close(fd[0]);

        long difference = stop.tv_usec - other_start.tv_usec;
        printf("seoncds: %ld\n", stop.tv_sec - other_start.tv_sec);
        printf("difference: %ld\n", difference * 100);
    }
    return 0;
}