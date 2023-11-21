#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define MAXLENGTH 4096
#define SERVER_PORT 5553

int main(){
    int client_socket;
    struct sockaddr_in servaddr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(client_socket < 0){
        perror("Error creating the socket.\n");
        exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0){
        perror("Error translating IP address from txt to binary form.\n");
        exit(1);
    }

    if(connect(client_socket, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        perror("Error connecting.\n");
        exit(1);
    }

    char message[] = "Hello";
    int n = write(client_socket, message, sizeof(message));
    if(n < 0){
        perror("Error writing message.\n");
        exit(1);
    }

    int size;
    printf("Please enter the size of the array: \n");
    scanf("%d", &size);

    int numbers[size];
    printf("Please enter %d numbers: \n", size);
    for(int i = 0; i < size; i++){
        scanf("%d", &numbers[i]);
    }

    n = write(client_socket, &size, sizeof(size));
    if(n < 0){
        perror("Error writing size.\n");
        exit(1);
    }

    n = write(client_socket, numbers, sizeof(numbers));
    if(n < 0){
        perror("Error writing numbers.\n");
        exit(1);
    }

    int sum;
    n = read(client_socket, &sum, sizeof(sum));
    if(n < 0){
        perror("Error reading sum.\n");
        exit(1);
    }

    printf("Sum received from server: %d\n", sum);

    close(client_socket);
    return 0;
}
