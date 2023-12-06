#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

void* process_thread(void* param) {
    printf("Executing thread\n");
    sem_post(&mutex);
    return NULL;
}

int main() {
    pthread_t thread_id;
    pthread_attr_t thread_attr;

    sem_init(&mutex, 0, 0);

    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

    if (pthread_create(&thread_id, &thread_attr, process_thread, NULL) != 0) {
        perror("Thread creation failed");
        return 1;
    }

    pthread_attr_destroy(&thread_attr);

    sem_wait(&mutex);

    printf("Thread completed\n");

    sem_destroy(&mutex);

    return 0;
}
