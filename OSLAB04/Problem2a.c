#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){

   pid_t myfork = fork();

   if (myfork <0){
    printf("Error");
   }
   else{

    if (myfork == 0){

        printf("Child1 Process PID= %d, PPID= %d\n", getpid(), getppid());

    }
    else {
        wait(NULL);
        printf("Parent Process PID= %d, PPID= %d\n", getpid(), getppid());
    }

   }





    return 0;
}