#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {

    printf("Main Process PID= %d, PPID=%d\n", getpid(), getppid());
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }

    if (pid == 0) {

        printf("Child Process PID= %d, PPID=%d\n", getpid(), getppid());
        sleep(5);
        printf("Ready to kill my parent!\n");
        kill(getppid(), SIGINT);
        printf("I am an orphan now\n");
    } else {
        wait(NULL);
        printf("I am the parent\n");
    }

    return 0;
}
