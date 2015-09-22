#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <errno.h>
#include "wrap.h"

#define MAXLINE 4096
#define SERV_PORT 8090
#define OPEN_MAX 65525 


int main(int argc,char *argv[])
{
    int i,j,maxi,listenfd,connfd,sockfd;
    int n;
    ssize_t nready,efd,res;
    char buf[MAXLINE],str[INET_ADDRSTRLEN];
    socklen_t clilen;
    struct sockaddr_in cliaddr,servaddr;

    struct epoll_event tep,ep[OPEN_MAX];

    listenfd = Socket(AF_INET,SOCK_STREAM,0);

    int opt = 1;
    //设置socket属性 取消2msl保护
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    Listen(listenfd,128);

    efd = epoll_create(OPEN_MAX);
    if(efd == -1)
        perr_exit("epoll_create");
    tep.events = EPOLLIN;//读数据
    tep.data.fd = listenfd;
    res = epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep);
    if(res == -1)
        perr_exit("epoll_ctl");

    for(;;)
    {
        nready = epoll_wait(efd,ep,OPEN_MAX,-1);
        //阻塞监听
        if(nready == -1)
            perr_exit("epoll_wait");
        for(i = 0; i < nready; ++i)
        {
            if(!(ep[i].events & EPOLLIN))//不是读事件跳过
                continue;
            if(ep[i].data.fd == listenfd)
            {
                clilen = sizeof(cliaddr);
                connfd = Accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
                printf("received from %s at PORT\n",inet_ntop(AF_INET,&cliaddr.sin_addr.s_addr,str,sizeof(str)));
                tep.events = EPOLLIN;
                tep.data.fd = connfd;
                res = epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&tep);
                if(res == -1)
                    perr_exit("epoll_ctl");
            }
            else 
            {
                sockfd = ep[i].data.fd;
                n = Read(sockfd,buf,MAXLINE);
                if(n <= 0)
                {
                    res = epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
                    if(res == -1)
                        perr_exit("epoll_ctl");
                    Close(sockfd);
                    printf("client[%d] closed connection\n",j);
                }
                else
                {
                    for(j = 0; j < n; ++j)
                        buf[j] = toupper(buf[j]);
                    Writen(sockfd,buf,n);
                }
            }
        }
    }
    Close(listenfd);
    Close(efd);
    return 0;
}
