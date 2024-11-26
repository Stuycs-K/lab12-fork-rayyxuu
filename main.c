#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        srand(getpid());
        int val = (rand()%5)+1;
        printf("%d %dsec\n", getpid(), val);
        sleep(val);
        printf("%d finished after %dsec\n", getpid(), val);
        exit(val);
    }
    else { //parent
        if (count==0) {
            count++;
            pid_t p2 = fork();
            if(p2<0){
                printerror();
                return 1;
            }
            else if (p2==0) { //child
                srand(getpid());
                int val = (rand()%5)+1;
                printf("%d %dsec\n", getpid(), val);
                sleep(val);
                printf("%d finished after %dsec\n", getpid(), val);
                exit(val);
            }
        }
        int stat;
        pid_t finalchild = wait(&stat);
        if (WIFEXITED(stat)){
            printf("Main Process %d is done. Child %d slept for %d sec\n", getpid(), finalchild, WEXITSTATUS(stat));
        }
    }
    return 0;
}
