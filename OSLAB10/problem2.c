#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex_lock;
float common_resource;

void* double_value(void* argument) {
    int thread_num = *((int*)argument);
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex_lock);
        common_resource *= 2;
        printf("Thread %d - Doubling the common resource... %.1f\n", thread_num, common_resource);
        pthread_mutex_unlock(&mutex_lock);
    }
    return NULL;
}

void* halve_value(void* argument) {
    int thread_num = *((int*)argument);
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex_lock);
        common_resource /= 2;
        printf("Thread %d - Halving the common resource... %.1f\n", thread_num, common_resource);
        pthread_mutex_unlock(&mutex_lock);
    }
    return NULL;
}

int main() {
    pthread_t thread_array[4];
    int thread_numbers[4] = {0, 1, 2, 3};

    printf("Input the starting value of the common resource: ");
    scanf("%f", &common_resource);
    printf("%.1f loaded\n", common_resource);

    pthread_mutex_init(&mutex_lock, NULL);
    for (int i = 0; i <= 1; i++) {
        pthread_create(&thread_array[i], NULL, double_value, (void*)&thread_numbers[i]);
    }
    for (int i = 2; i <= 3; i++) {
        pthread_create(&thread_array[i], NULL, halve_value, (void*)&thread_numbers[i]);
    }
    for (int i = 0; i <= 3; i++) {
        pthread_join(thread_array[i], NULL);
    }
    printf("Final value of the common resource is %.1f\n", common_resource);

    pthread_mutex_destroy(&mutex_lock);
    return 0;
}
