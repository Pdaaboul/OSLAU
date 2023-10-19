#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int N;
    int *shared_array;

    printf("Please enter the size of the array:\n");
    scanf("%d", &N);
    shared_array = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    pid_t child1_pid = fork();

    if (child1_pid == 0) {
        pid_t child3_pid = fork();
        if (child3_pid == 0) {
            printf("*** From Child 3: ***\nPlease enter %d integers:\n", N);
            for (int i = 0; i < N; ++i) {
                scanf("%d", &shared_array[i]);
                printf("%d ", shared_array[i]);
            }
            printf("\n");
            exit(0);
        }
        wait(NULL);
        printf("*** From Child 1: ***\n");
        for (int i = 0; i < N; ++i) {
            shared_array[i] *= 10;
            printf("%d ", shared_array[i]);
        }
        printf("\n");
        exit(0);
    }
    
    wait(NULL);

    pid_t child2_pid = fork();
    if (child2_pid == 0) {
        printf("*** From Child 2: ***\n");
        for (int i = 0; i < N; ++i) {
            shared_array[i] -= 2;
            printf("%d ", shared_array[i]);
        }
        printf("\n");
        exit(0);
    }

    wait(NULL);

    int sum = 0;
    printf("*** From Parent: ***\n");
    for (int i = 0; i < N; ++i) {
        sum += shared_array[i];
        printf("%d ", shared_array[i]);
    }
    printf("\n");

    int new_N = N + 1;
    shared_array = mremap(shared_array, N * sizeof(int), new_N * sizeof(int), 0);
    shared_array[N] = sum;
    printf("%d\n", sum);

    munmap(shared_array, new_N * sizeof(int));

    return 0;
}
