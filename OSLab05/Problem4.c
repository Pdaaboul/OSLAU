#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
        pid_t child1 = fork();

        if (child1<0){
            printf("error");
            return 1;
        }
        else if (child1 == 0){
            pid_t child2 = fork();
            if (child2<0){
                printf("error");
                return 1;
            }
            else if(child2<0){
                printf("error");
                return 1;
            }
            else if (child2 == 0){
                for (int i = 1; i <= 10; i ++){

                printf ("Child 2: PID = %d, PPID = %d, Number = %d \n", getpid(), getppid(), i);
                }
            }
            else{
                wait(NULL);
                   for (int i = 11; i <= 20; i ++){

                printf ("Child 1: PID = %d, PPID = %d, Number = %d \n", getpid(), getppid(), i);

            }
        }

        }
        else {
            wait(NULL);
               for (int i = 21; i <= 30; i ++){

                printf ("Parent: PID = %d, PPID = %d, Number = %d \n", getpid(), getppid(), i);

        }
        }
    return 0;
}