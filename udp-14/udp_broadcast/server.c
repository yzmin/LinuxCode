#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>

#define SERVER_PORT 8000
#define CLIENT_PORT 9000
#define MAXLINE 4096

#define BROADCAST_IP "192.168.152.255"

int main(void)
{
    int sockfd,i;
    struct sockaddr_in serveraddr,clientaddr;
    char buf[MAXLINE] = "yzmin\n";
    char ipstr[INET_ADDRSTRLEN];
    socklen_t clientlen;
    ssize_t len;
    struct ip_mreqn group;
    //构造用于UDP通信的套接字
    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVER_PORT);
    bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

    int flag = 1;//开启广播
    setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&flag,sizeof(flag));

    //构造 client 地址 IP+端口
    bzero(&clientaddr,sizeof(clientaddr));
    clientaddr.sin_family = AF_INET;
    inet_pton(AF_INET,BROADCAST_IP,&clientaddr.sin_addr.s_addr);
    clientaddr.sin_port = htons(CLIENT_PORT);

    while(1)
    {
        //fgets(buy,sizeof(buf),stdin);
        sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
        sleep(1);
    }
    close(sockfd);
    return 0;
}
