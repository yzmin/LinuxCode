/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "wrap.h"
#define MAXLINE 4096
#define SERV_PORT 8090

int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE] = "heel";
    int sockfd, n;
    if(argc < 2)
    {
        printf("./client IP\n");
        exit(1);
    }

    while(1)
    {
        sockfd = Socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
        servaddr.sin_port = htons(SERV_PORT);

        Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        //Close(sockfd);
    }
    return 0;
}

