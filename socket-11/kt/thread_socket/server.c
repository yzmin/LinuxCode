#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>
#include "wrap.h"

#define SERV_IP "192.168.152.128"
#define SERV_PORT 8090
#define MAXLINE 4096

struct sock_task
{
    int cfd;
    struct sockaddr_in clie_addr;
};


void *do_task(void *arg)
{
    //处理客户端数据
    struct sock_task *task = (struct sock_task *)arg;
    int len,i;
    char buf[MAXLINE],clie_ip[128];

    pthread_detach(pthread_self());

    while(1)
    {
again:
        len = Read(task->cfd,buf,sizeof(buf));
        if(len == 0)
        {
            printf("client %s is close\n",inet_ntop(AF_INET,&task->clie_addr.sin_addr.s_addr,clie_ip,sizeof(clie_ip)));
            Close(task->cfd);
            pthread_exit(0);
        }
        else if(len < 0)
        {
            goto again;
        }

        for(i = 0; i < len; i++)
            buf[i] = toupper(buf[i]);

        Write(task->cfd,buf,len);
    }
}

int main(void)
{
    int sfd,cfd,len,i = 0;
    char buf[MAXLINE],clie_ip[128];

    struct sockaddr_in serv_addr,clie_addr;
    socklen_t clie_len;
    pthread_t tid; 
    struct sock_task task[1024];

    sfd = Socket(AF_INET,SOCK_STREAM,0);

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(SERV_PORT);

    Bind(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    Listen(sfd,128);//不阻塞

    while(1)
    {
        clie_len = sizeof(clie_addr);
        cfd = Accept(sfd,(struct sockaddr *)&clie_addr,&clie_len);
        printf("recive client %s\t%d connect\n",inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,clie_ip,sizeof(clie_ip)),ntohs(clie_addr.sin_port));
        
        task[i].cfd = cfd;
        task[i].clie_addr = clie_addr;
        pthread_create(&tid,NULL,do_task,(void *)&task[i]);
        i++;
    }
    
    Close(sfd);

    return 0;
}
