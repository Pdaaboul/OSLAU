#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 10

typedef struct {
    int id;
    char category;
} Item;

typedef struct {
    Item buffer[BUFFER_SIZE];
    int in;
    int out;
} SharedBuffer;

char determineCategory(int id) {
    if (id % 2 == 0) return 'E';
    if (id % 5 == 0) return '*';
    return 'O';
}

void produce(SharedBuffer *buf, int id) {
    char category = determineCategory(id);
    Item item = {id, category};
    buf->buffer[buf->in] = item;
    buf->in = (buf->in + 1) % BUFFER_SIZE;
    printf("Produced item:  %d-%c\n", id, category);
}

Item consume(SharedBuffer *buf) {
    Item item = buf->buffer[buf->out];
    buf->out = (buf->out + 1) % BUFFER_SIZE;
    printf("Consumed item:  %d-%c\n", item.id, item.category);
    return item;
}

int main() {
    SharedBuffer *sharedBuffer;
    sharedBuffer = mmap(NULL, sizeof(SharedBuffer), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    sharedBuffer->in = 0;
    sharedBuffer->out = 0;

    pid_t pid = fork();
    if (pid < 0) {
        printf("fork failed");
        return 1;
    } else if (pid == 0) { 
        for (int i = 0; i < 30; i++) {
            while (sharedBuffer->in == sharedBuffer->out);
            consume(sharedBuffer);
        }
    } else { 
        int next_id = 2023001;
        for (int i = 0; i < 30; i++) {
            while ((sharedBuffer->in + 1) % BUFFER_SIZE == sharedBuffer->out); 
            produce(sharedBuffer, next_id++);
        }
        wait(NULL);
    }


    munmap(sharedBuffer, sizeof(SharedBuffer));
    return 0;
}
