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
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        gettimeofday(&start, NULL);
        long begin = start.tv_sec;
        printf("fork begin: %ld\n", begin);

        //write(fd[1], &begin, sizeof(double));
        close(fd[1]);

    } else {
        wait(NULL);
        close(fd[1]);

        gettimeofday(&stop, NULL);
        long end;
        
        //read(fd[0], &end, sizeof(double));
        dup2(fd[0],stdin);
        scanf("%ld", &end);
        close(fd[0]);
        difference = (stop.tv_sec - end);
        printf("Main begin: %ld\n", end);
        printf("stop: %ld\n", stop.tv_sec);
        //printf("%d")
        printf("Time: %ld\n", difference);

    }


    return 0;
}