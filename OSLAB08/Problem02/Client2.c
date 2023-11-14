#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 7015

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello_server = "hello";
    int sum = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    send(sock, hello_server, strlen(hello_server), 0);
    printf("received: hello client\n");

    printf("please enter the size of the array: ");
    int array_size;
    scanf("%d", &array_size);

    int* num_array = malloc(array_size * sizeof(int));

    printf("Please enter %d numbers: ", array_size);
    for (int i = 0; i < array_size; i++) {
        scanf("%d", &num_array[i]);
    }

    send(sock, &array_size, sizeof(array_size), 0);
    send(sock, num_array, array_size * sizeof(int), 0);

    read(sock, &sum, sizeof(sum));
    printf("sum %d\n", sum);

    free(num_array);
    close(sock);

    return 0;
}