#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

char command[999];
printf("Enter a command to execute: ");
fgets(command, sizeof(command), stdin);
pid_t child1 = fork();

if (child1 <0){
    printf("error");
    return 1;
}
if (child1 == 0){

    execlp("zsh", "zsh", "-c", command, NULL);
}
    
if (child1 >0){
    printf("Parent process: Created child process with PID %d\n", child1);
    wait(NULL);
   printf("Parent process: Child process completed");
}

    return 0;
}