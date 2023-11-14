#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define SERV_PORT 7015
#define SERVER_IP "127.0.0.1" 

int main() {
    int sockfd, n;
    char sendline[MAXLINE], recvline[MAXLINE];
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);

    if (inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr) <= 0) {
        fprintf(stderr, "inet_pton error for %s\n", SERVER_IP);
        return 1;
    }

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect error");
        return 1;
    }

    strcpy(sendline, "Hello Server");
    write(sockfd, sendline, strlen(sendline));

    n = read(sockfd, recvline, MAXLINE-1);
    if (n < 0) {
        perror("read error");
        return 1;
    }
    recvline[n] = 0;
    printf("Server says: %s\n", recvline);

    printf("Enter a string: ");
    fgets(sendline, MAXLINE, stdin);

    sendline[strlen(sendline) - 1] = '\0';
    size_t len = strlen(sendline);
    if (len > 0 && sendline[len-1] == '\n') sendline[len-1] = 0;

    printf("Enter a character: ");
    char c;
    scanf(" %c", &c);

    len = strlen(sendline);
    sendline[len] = ' ';
    sendline[len + 1] = c;
    sendline[len + 2] = 0;

    write(sockfd, sendline, strlen(sendline));

    n = read(sockfd, recvline, MAXLINE-1);
    if (n < 0) {
        perror("read error");
        return 1;
    }
    recvline[n] = 0;
    printf("Occurrences: %s\n", recvline);

    close(sockfd);

    return 0;
}
