#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "wrap.h"

#define SERV_PROT 8090
#define SERV_IP "192.168.152.128"

int main(void)
{
    int cfd,len;
    struct sockaddr_in saddr;
    char buf[4096] = "helloworld";

    cfd = Socket(AF_INET,SOCK_STREAM,0);

    bzero(&saddr,sizeof(saddr));
    saddr.sin_family = AF_INET;
    inet_pton(AF_INET,SERV_IP,(void*)&saddr.sin_addr.s_addr);//目标器的ip地址
    saddr.sin_port = htons(SERV_PROT);

    Connect(cfd,(struct sockaddr *)&saddr,sizeof(saddr));

    while(fgets(buf,sizeof(buf),stdin) != NULL)
    {
        Write(cfd,buf,strlen(buf));
        len = read(cfd,buf,sizeof(buf));
        Write(STDOUT_FILENO,buf,len);
    }

    Close(cfd);

    return 0;
}
