#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 4
#define RANGE 250  

int array[ARRAY_SIZE];


int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i <= num / 2; i++) { 
        if (num % i == 0) return 0;
    }
    return 1;
}


void *process_array_segment(void *arg) {
    int thread_id = *(int *)arg;
    int start = thread_id * RANGE;
    int end = start + RANGE;

    printf("Thread %d processing elements from index %d to index %d\n", thread_id, start, end - 1);

    for (int i = start; i < end; i++) {
        if (!is_prime(array[i])) {
            array[i] = 0;
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    
    srand(time(NULL));

    
    printf("Initial array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100 + 1;
        printf("%d ", array[i]);
    }
    printf("\n\n");

    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, process_array_segment, (void *)&thread_args[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    
    printf("Modified array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
