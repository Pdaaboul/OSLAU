#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_COUNT 8

double sharedData;
int value1, value2;

pthread_mutex_t dataLock;

void *increment(void *arg) {
    long threadNum = (long)arg;
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&dataLock);
        sharedData += value1;
        printf("Thread %ld - Incrementing by %d... sharedData=%.1f\n", threadNum, value1, sharedData);
        pthread_mutex_unlock(&dataLock);
    }
    return NULL;
}

void *decrement(void *arg) {
    long threadNum = (long)arg;
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&dataLock);
        sharedData -= value1;
        printf("Thread %ld - Decrementing by %d... sharedData=%.1f\n", threadNum, value1, sharedData);
        pthread_mutex_unlock(&dataLock);
    }
    return NULL;
}

void *amplify(void *arg) {
    long threadNum = (long)arg;
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&dataLock);
        sharedData *= value2;
        printf("Thread %ld - Amplifying by %d... sharedData=%.1f\n", threadNum, value2, sharedData);
        pthread_mutex_unlock(&dataLock);
    }
    return NULL;
}

void *reduce(void *arg) {
    long threadNum = (long)arg;
    for (int i = 0; i < 3; ++i) {
        pthread_mutex_lock(&dataLock);
        if (value2 != 0) {
            sharedData /= value2;
        }
        printf("Thread %ld - Reducing by %d... sharedData=%.1f\n", threadNum, value2, sharedData);
        pthread_mutex_unlock(&dataLock);
    }
    return NULL;
}

int main() {
    pthread_t threadArray[THREAD_COUNT];
    pthread_mutex_init(&dataLock, NULL);

    printf("Enter the initial value for sharedData: ");
    scanf("%lf", &sharedData);
    printf("Enter values for value1 and value2: ");
    scanf("%d %d", &value1, &value2);

    for (long i = 0; i < 4; ++i) {
        if (i < 2) pthread_create(&threadArray[i], NULL, increment, (void *)i);
        else pthread_create(&threadArray[i], NULL, decrement, (void *)i);
    }

    for (int i = 0; i < 4; ++i) {
        pthread_join(threadArray[i], NULL);
    }

    for (long i = 4; i < THREAD_COUNT; ++i) {
        if (i < 6) pthread_create(&threadArray[i], NULL, amplify, (void *)i);
        else pthread_create(&threadArray[i], NULL, reduce, (void *)i);
    }

    for (int i = 4; i < THREAD_COUNT; ++i) {
        pthread_join(threadArray[i], NULL);
    }

    printf("Final value of sharedData is %.1f\n", sharedData);

    pthread_mutex_destroy(&dataLock);
    return 0;
}
