#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

void printArray(int* arr, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    printf("Length N=%d\n", N);

    int* sharedArray = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (sharedArray == MAP_FAILED) {
        printf("mmap failed");
        return 1;
    }

    pid_t childPid = fork();

    if (childPid < 0) {
        printf("Fork failed");
        return 1;
    }

    if (childPid == 0) { 
        printf("From Child, please enter %d integers:\n", N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &sharedArray[i]);
        }

        
        printArray(sharedArray,N);

       
    } else { 
        wait(NULL);

        printf("From Parent, please enter a:\n");
        int a;
        scanf("%d", &a);

        for (int i = 0; i < N; i++) {
            sharedArray[i] *= a;
        }

    
        printArray(sharedArray, N);
    }

    munmap(sharedArray, N * sizeof(int));
    return 0;
}
