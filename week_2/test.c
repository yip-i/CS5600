#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>

int main(){

    mode_t mode = S_IRUSR | S_IWUSR;
    int i = 0, fd, pid;
    unsigned char pi1 = 0x33, pi2 = 0x34;
    if((fd = open("res", O_RDWR | O_CREAT | O_TRUNC, mode)) < 0){

        perror("open error");
        exit(1);
    }

    if((pid = fork()) < 0){

       perror("fork error");
       exit(1);
    }

    if(pid == 0) {


        if (write(fd, "Hello World", 12) != 12) {

           perror("write error");
           exit(1);
       }  
    }else{

        if (write(fd, "Hello World1", 13) != 13) {

           perror("write error");
           exit(1);
       }  
    }

    //close(fd);
    return 0;
}