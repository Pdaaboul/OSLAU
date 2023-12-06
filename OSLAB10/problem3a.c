#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TOTAL_THREADS 8

double shared_val;
int param_x, param_y, param_z, param_w;

pthread_mutex_t sync_lock;

void *increment(void *arg) {
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&sync_lock);
        shared_val += param_x;
        printf("Thread %ld - Incrementing by %d... shared_val=%.1f\n", (long)arg, param_x, shared_val);
        pthread_mutex_unlock(&sync_lock);
    }
    return NULL;
}

void *decrement(void *arg) {
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&sync_lock);
        shared_val -= param_y;
        printf("Thread %ld - Decrementing by %d... shared_val=%.1f\n", (long)arg, param_y, shared_val);
        pthread_mutex_unlock(&sync_lock);
    }
    return NULL;
}

void *product(void *arg) {
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&sync_lock);
        shared_val *= param_z;
        printf("Thread %ld - Multiplying by %d... shared_val=%.1f\n", (long)arg, param_z, shared_val);
        pthread_mutex_unlock(&sync_lock);
    }
    return NULL;
}

void *quotient(void *arg) {
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&sync_lock);
        if (param_w != 0) {
            shared_val /= param_w;
        }
        printf("Thread %ld - Dividing by %d... shared_val=%.1f\n", (long)arg, param_w, shared_val);
        pthread_mutex_unlock(&sync_lock);
    }
    return NULL;
}

int main() {
    pthread_t thread_array[TOTAL_THREADS];
    pthread_mutex_init(&sync_lock, NULL);

    printf("Enter the starting value for shared_val: ");
    scanf("%lf", &shared_val);
    printf("Enter values for param_x, param_y, param_z, and param_w: ");
    scanf("%d %d %d %d", &param_x, &param_y, &param_z, &param_w);

    for (long i = 0; i < TOTAL_THREADS; ++i) {
        if (i < 2) pthread_create(&thread_array[i], NULL, increment, (void *)i);
        else if (i < 4) pthread_create(&thread_array[i], NULL, decrement, (void *)i);
        else if (i < 6) pthread_create(&thread_array[i], NULL, product, (void *)i);
        else pthread_create(&thread_array[i], NULL, quotient, (void *)i);
    }

    for (int i = 0; i < TOTAL_THREADS; ++i) {
        pthread_join(thread_array[i], NULL);
    }

    printf("Final value of shared_val is %.1f\n", shared_val);

    pthread_mutex_destroy(&sync_lock);
    return 0;
}
