
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 7015

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) { 
        printf("Waiting for a connection...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            continue; 
        }

        printf("Connection established\n");

        char buffer[1024] = {0};
        ssize_t bytes_read = read(new_socket, buffer, sizeof(buffer));
        printf("Received: %s\n", buffer);

        printf("Waiting for client to send an array\n");
        int array_size = 0;
        read(new_socket, &array_size, sizeof(array_size));
        printf("Number of bytes read = %d; thus %d is the size of the array\n", array_size * (int)sizeof(int), array_size);

        int* num_array = malloc(array_size * sizeof(int));
        bytes_read = read(new_socket, num_array, array_size * sizeof(int));
        for (int i = 0; i < array_size; ++i) {
            printf("%d ", num_array[i]);
        }
        printf("\nfinished reading\ncomputing sum\n");

        int sum = 0;
        for (int i = 0; i < array_size; ++i) {
            sum += num_array[i];
        }
        printf("Sum: %d\n", sum);

        send(new_socket, &sum, sizeof(sum), 0);

        free(num_array);
        close(new_socket); 

        printf("Connection closed. Ready for new connection.\n");
    }

    return 0;
}
