#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main (){
    pid_t child1 = fork();

    if (child1 == 0){
        pid_t child3 = fork();
        if (child3 == 0){
            printf("Child3 Process PID= %d, PPID=%d \n",getpid(), getppid());
        }
        else{
            wait(NULL);
            printf("Child1 Process PID= %d, PPID=%d \n",getpid(), getppid());
        }
    }

    else if (child1 > 0){
        pid_t child2 = fork();
        if (child2 == 0){
            printf("Child2 Process PID= %d, PPID=%d \n",getpid(), getppid());
        }
        else if (child1 > 0 && child2 > 0){
            wait(NULL);
            wait(NULL);
            printf("Parent Process PID= %d, PPID=%d\n",getpid(),getppid());
        }
    }

    return 0;
}
