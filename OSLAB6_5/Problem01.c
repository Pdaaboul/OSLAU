#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
} SharedBuffer;

void produce(SharedBuffer *buf, int item) {
    buf->buffer[buf->in] = item;
    buf->in = (buf->in + 1) % BUFFER_SIZE;
    printf("Produced item:  %d\n", item);
}

int consume(SharedBuffer *buf) {
    int item = buf->buffer[buf->out];
    buf->out = (buf->out + 1) % BUFFER_SIZE;
    printf("Consumed item:  %d\n", item);
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
        for (int i = 0; i < 20; i++) {
            while (sharedBuffer->in == sharedBuffer->out); 
            consume(sharedBuffer);
        }
    } else { 
        int next_item_to_produce = 2023001;

        for (int i = 0; i < 20; i++) {
            while ((sharedBuffer->in + 1) % BUFFER_SIZE == sharedBuffer->out); 
            produce(sharedBuffer, next_item_to_produce++);
        }

        wait(NULL);
    }

    
    munmap(sharedBuffer, sizeof(SharedBuffer));
    return 0;
}
