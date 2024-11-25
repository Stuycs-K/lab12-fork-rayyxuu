#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int printerror(){
    printf("error number %d\n",errno);
    printf("error: %s\n", strerror(errno));
    return 0;
}

int main(){
    static int count = 0;
    printf("%d about to create 2 child processes\n", getpid());
    pid_t p = fork();
    if(p<0){
        printerror();
        return 1;
    }
    else if (p==0) { //child
        int val = rand()%(6);
        printf("%d %dsec\n", getpid(), val);
        sleep(val);
        printf("%d finished after %dsec\n", getpid(), val);
    }
    else { //parent
        if (count==0) {
            count++;
            pid_t p2 = fork();
            if(p<0){
                printerror();
                return 1;
            }
            else if (p==0) { //child
                int val = rand()%(6);
                printf("%d %dsec\n", getpid(), val);
                sleep(val);
                printf("%d finished after %dsec\n", getpid(), val);
            }
            else { //parent
                int* stat;
                wait(stat);
                printf("Main Process _PID_ is done. Child _EXITING_CHILD_PID_ slept for _SEC_ sec\n");
            }
        }
    }
    return 0;
}
