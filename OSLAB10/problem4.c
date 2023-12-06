#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int rest() {
    struct timespec duration;
    int seconds = rand() % 3;
    int nanoseconds = rand() % 999999999;
    duration.tv_sec = seconds;
    duration.tv_nsec = nanoseconds;
    nanosleep(&duration, NULL);
    return 0;
}

sem_t *forks;

void* dine(void* arg) {
    int philosopher_id = *(int*)arg;

    while (1) {
        printf("Philosopher %d is pondering.\n", philosopher_id);
        rest(); 

        printf("Philosopher %d feels famished.\n", philosopher_id);
        if (philosopher_id % 2 == 0) { 
            sem_wait(&forks[(philosopher_id + 1) % 5]); 
            sem_wait(&forks[philosopher_id]);             
        } else { 
            sem_wait(&forks[philosopher_id]);             
            sem_wait(&forks[(philosopher_id + 1) % 5]); 
        }

        printf("Philosopher %d is now eating.\n", philosopher_id);
        rest(); 

        sem_post(&forks[philosopher_id]);             
        sem_post(&forks[(philosopher_id + 1) % 5]); 
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please specify the number of philosophers.");
        return 1;
    }
    int philosopher_count = atoi(argv[1]);
    
    pthread_t philosophers[philosopher_count];
    
    int philosopher_nums[philosopher_count];
    forks = malloc(philosopher_count * sizeof(sem_t));
    srand(time(NULL)); 
    for (int i = 0; i < philosopher_count; i++) {
        sem_init(&forks[i], 0, 1);
    }
    for (int i = 0; i < philosopher_count; i++) {
        philosopher_nums[i] = i;
        pthread_create(&philosophers[i], NULL, dine, (void*)&philosopher_nums[i]);
    }
    for (int i = 0; i < philosopher_count; i++) {
        pthread_join(philosophers[i], NULL);
    }
    free(forks);
    return 0;
}
