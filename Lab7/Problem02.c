#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1
#define BUFFER_SIZE 100

int main() {
    int fd1[2], fd2[2];
    pid_t pid;
    char write_msg[BUFFER_SIZE], read_msg[BUFFER_SIZE];
    int bytes_read, bytes_written;

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid > 0) {
        
        close(fd1[WRITE_END]);
        close(fd2[READ_END]);

        
        bytes_read = read(fd1[READ_END], read_msg, BUFFER_SIZE);
        read_msg[bytes_read] = '\0';
        printf("Parent reads %s\n", read_msg);
        printf("Parent reads %d bytes\n", bytes_read);

        
        printf("Parent: Bytes received=%d\n", bytes_read);

        
        write(fd2[WRITE_END], &bytes_read, sizeof(bytes_read));

        close(fd1[READ_END]);
        close(fd2[WRITE_END]);
        wait(NULL);
    } else {
        
        close(fd1[READ_END]);
        close(fd2[WRITE_END]);

        
        printf("Enter a string\n");
        fgets(write_msg, BUFFER_SIZE, stdin);
        write_msg[strcspn(write_msg, "\n")] = 0;

        
        bytes_written = write(fd1[WRITE_END], write_msg, strlen(write_msg));
        printf("Child wrote %s\n", write_msg);
        printf("Child wrote %d bytes\n", bytes_written);

        
        read(fd2[READ_END], &bytes_read, sizeof(bytes_read));
        printf("Child: Bytes received from parent=%d\n", bytes_read);
        printf("Child: Number of characters received=%ld\n", strlen(write_msg));

        if (bytes_written == bytes_read) {
            printf("Child ==>Message successfully received!!\n");
        }

        close(fd1[WRITE_END]);
        close(fd2[READ_END]);
    }

    return 0;
}
