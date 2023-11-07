#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]) {
    int fd[2];
    pid_t pid;
    char c, read_char;
    int count, status;

    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid == 0) {
    
        close(fd[WRITE_END]);
        count = 0;
        while (read(fd[READ_END], &read_char, 1) > 0 && read_char != '*') {
            count++;
        }
        printf("Child: Read = %d\n", count);

    
        read(fd[READ_END], &c, 1);
        int occurrences = 0;
        for (int i = 1; i < argc; i++) {
            for (char *ptr = argv[i]; *ptr; ptr++) {
                if (*ptr == c) occurrences++;
            }
        }
        close(fd[READ_END]);
        exit(occurrences);
    }   else {
        // Parent process

        close(fd[READ_END]);
        for (int i = 1; i < argc; i++) {
            write(fd[WRITE_END], argv[i], strlen(argv[i]));
        }
        write(fd[WRITE_END], "*", 1);

      
        printf("Parent: Please enter character c:\n");
        scanf(" %c", &c);
        write(fd[WRITE_END], &c, 1);

        close(fd[WRITE_END]);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Parent ==> Occurrence of letter '%c' received from Child = %d\n", c, WEXITSTATUS(status));
        }
    }

    return 0;
}
