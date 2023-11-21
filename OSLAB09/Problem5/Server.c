#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SERVER_PORT 5553
#define BACKLOG 10
#define MAXLINE 4096

void *client_handler(void *arg);

int main(){
    int client_socket;
    int server_socket;
    struct sockaddr_in servaddr;
    pthread_t thread_id;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0){
        perror("Error creating the socket.\n");
        exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);

    if(bind(server_socket, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        perror("Binding error.\n");
        exit(1);
    }

    if(listen(server_socket, BACKLOG) < 0){
        perror("Listening error.\n");
        exit(1);
    }

    while(1){
        client_socket = accept(server_socket, NULL, NULL);

        if(client_socket < 0){
            perror("Error accepting connection.\n");
            continue;
        }

        if(pthread_create(&thread_id, NULL, client_handler, (void*)&client_socket) != 0){
            perror("Could not create thread.\n");
            close(client_socket);
        }

        pthread_detach(thread_id);
    }

    close(server_socket);
    return 0;
}

void *client_handler(void *socket_desc){
    int sock = *(int*)socket_desc;
    char buffer[MAXLINE];
    int n = read(sock, buffer, MAXLINE - 1);
    if(n < 0){
        perror("Error reading message.\n");
        close(sock);
        return NULL;
    }
    buffer[n] = '\0';
    printf("Received: %s\n\nWaiting for the client to send the array.\n", buffer);

    int size;
    n = read(sock, &size, sizeof(size));
    if(n < 0){
        perror("Error reading size.\n");
        close(sock);
        return NULL;
    }

    int numbers[size];
    int sum = 0;

    n = read(sock, numbers, sizeof(numbers));
    if(n < 0){
        perror("Error reading numbers.\n");
        close(sock);
        return NULL;
    }
    printf("Number of bytes read = %d, thus %d is the size of the array.\n", n, n / 4);
    printf("Computing sum.\n");

    for(int i = 0; i < size; i++){
        sum += numbers[i];
    }
    printf("Sum: %d\n", sum);

    n = write(sock, &sum, sizeof(sum));
    if(n < 0){
        perror("Error sending sum.\n");
    }

    close(sock);
    return NULL;
}
