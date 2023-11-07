#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pipe1[2], pipe2[2]; 
    pid_t p;
    int N, num, positiveCount = 0;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    
    p = fork();

    if (p < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    } 
    else if (p > 0) { 
        printf("Parent ==> Enter N the number of integers in the list:\n");
        scanf("%d", &N);
        close(pipe1[0]); 
        write(pipe1[1], &N, sizeof(N)); 

        close(pipe2[1]); 
        printf("The parent received:");
        for (int i = 0; i < N; i++) {
            read(pipe2[0], &num, sizeof(num));
            printf("%d ", num);
            if (num > 0) positiveCount++;
        }
        printf("\nParent ==> the number of positive integers is %d\n", positiveCount);
        close(pipe2[0]); 

        write(pipe1[1], &positiveCount, sizeof(positiveCount)); 
        close(pipe1[1]); 
    } 
    else { 
        close(pipe1[1]);
        read(pipe1[0], &N, sizeof(N));

        int arr[N];
        printf("Child ==> Enter %d integers:\n", N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }

        close(pipe2[0]); 
        for (int i = 0; i < N; i++) {
            write(pipe2[1], &arr[i], sizeof(arr[i]));
        }
        close(pipe2[1]); 

        read(pipe1[0], &positiveCount, sizeof(positiveCount)); 
        printf("Child ==> The number of positive integers is %d\n", positiveCount);
        close(pipe1[0]); 
    }

    return 0;
}
