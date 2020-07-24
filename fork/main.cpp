#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
    int i;
    pid_t pid;
    printf("aaaaaaaaaaaaaaaaaaaa\n");

    for(i = 0; i < 5; i++){
        pid = fork();
        if(pid == 0) {
            break;
        }
    }

    if(i < 5) {
        sleep(i);
        printf("I'm %d child, pid = %u, uid = %u, ppid = %u\n",
                i + 1, getpid(), getuid(), getppid());
    }else{
        sleep(i);
        printf("I'm parent\n");
    }






    return 0;
}