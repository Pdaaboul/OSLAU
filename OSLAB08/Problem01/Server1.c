#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define BACKLOG 10
#define SERV_PORT 7015

int main() {
    int listenfd, connfd, n;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    char response[] = "Hello Client";

   
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

   
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

   
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind error");
        exit(1);
    }

   
    if (listen(listenfd, BACKLOG) < 0) {
        perror("listen error");
        exit(1);
    }

    printf("Server is listening on port %d...\n", SERV_PORT);

   
    while (1) {
   
        if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) < 0) {
            perror("accept error");
            continue;
        }

   
        n = read(connfd, buff, MAXLINE-1);
        if (n < 0) {
            perror("read error");
            close(connfd);
            continue;
        }
        buff[n] = 0; 
        printf("Received from client: %s\n", buff);
        
   
        write(connfd, response, strlen(response));

   
        n = read(connfd, buff, MAXLINE-1);
        if (n < 0) {
            perror("read error");
            close(connfd);
            continue;
        }
        buff[n] = 0; 

        printf("Waiting for the client to send the string s and character c\n");
        printf("Number of bytes read = %d\n", n-2);

   
        char *s = strtok(buff, " ");
        char c = s[strlen(s) + 1]; 
        printf("String received: %s\n", s);
        printf("Character Received: %c\n", c);

   
        int count = 0;
        for (int i = 0; s[i] != '\0'; i++) {
            if (s[i] == c) count++;
        }
        printf("Count: %d\n", count);

       
        sprintf(buff, "%d", count);
        write(connfd, buff, strlen(buff));

        close(connfd);
    }

    return 0;
}
