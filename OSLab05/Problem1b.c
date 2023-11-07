#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>


int main(){
    pid_t child1 = fork();
    if (child1<0){
       printf("Fork failed for Child1.\n");
        return 1;
        
        
    }
    if (child1 == 0){
            printf("Child1 Process PID= %d, PPID=%d\n", getpid(),getppid());

    }

    else if (child1>0){
        wait(NULL);
        pid_t child2 = fork();
        if (child2 <0){
              printf("Fork failed for Child3.\n");
              return 1;
        }
        else if (child2 == 0){
            printf("Child2 Process PID= %d, PPID=%d\n", getpid(),getppid());
        }
        else if (child2 >0){
            wait(NULL);
            pid_t child3 = fork();
            if (child3<0){
                printf("Fork failed for Child3.\n");
                return 1;
            }
            else if (child3 ==0){
                printf("Child3 Process PID= %d, PPID=%d\n", getpid(),getppid());
            }
            else {
                wait(NULL);
                printf("Parent Process PID= %d, PPID=%d",getpid(),getppid());
            }


        }
    }





    return 0;
}