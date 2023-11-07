#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main() {
    int fd[2];
    pid_t pid;

    // Creating a pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    // Forking a child
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(fd[READ_END]); // Close unused read end

        // Redirect stdout to pipe
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[WRITE_END]);

        // Execute pwd
        execlp("/bin/pwd", "pwd", NULL);
        exit(EXIT_FAILURE); // Execute only if execlp fails
    } else {
        // Parent process
        close(fd[WRITE_END]); // Close unused write end

        // Redirect stdin to pipe
        dup2(fd[READ_END], STDIN_FILENO);
        close(fd[READ_END]);

        // Execute wc -c
        execlp("/usr/bin/wc", "wc", "-c", NULL);
        wait(NULL); // Wait for child process
    }

    return 0;
}
