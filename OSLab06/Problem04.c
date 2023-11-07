#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int *shared_value;
    
    
    shared_value = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    
    printf("Enter a positive integer: ");
    scanf("%d", shared_value);

    
    if (*shared_value <= 0) {
        printf("Error: The integer should be positive!\n");
        return 1;
    }

    
    pid_t child_pid = fork();
    
    if (child_pid == 0) {
    
        int result = 1;
        for (int i = 1; i <= *shared_value; ++i) {
            result *= i;
        }
        *shared_value = result;
        exit(0);
    } else {
    
        wait(NULL);

    
        printf("Factorial of %d is: %d\n", *shared_value, *shared_value);

    
        munmap(shared_value, sizeof(int));
    }

    return 0;
}
