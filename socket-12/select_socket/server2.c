#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8090

int main(int argc,char *argv[])
{
    int i, maxi, maxfd,listenfd, connfd, sockfd;
    int nready, client[FD_SETSIZE];//FD_SETSIZE 默认为1024
    ssize_t n;
    fd_set rset, allset;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN]; //#define INET_ADDRSTRLEN 16
    socklen_t clie_len;
    struct sockaddr_in serv_addr, clie_addr;

    listenfd = Socket(AF_INET,SOCK_STREAM,0);

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    Bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    Listen(listenfd,20);//默认最大128

    maxfd = listenfd;//初始化最大值
    maxi = -1;//client[]的下标

    for(i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;//用-1初始化client[]

    FD_ZERO(&allset);
    FD_SET(listenfd,&allset);//构造select监控文件描述符集

    for(;;)
    {
        rset = allset;//每次循环都从新设置select监控信号集
        nready = select(maxfd+1,&rset,NULL,NULL,NULL);
        if(nready < 0)
            perr_exit("select err");

        //监控是否有新链接
        if(FD_ISSET(listenfd,&rset))
        {
            clie_len = sizeof(clie_addr);
            connfd = Accept(listenfd,(struct sockaddr *)&clie_addr,&clie_len);
            printf("received from %s at PORT %d\n",inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,str,sizeof(str)),ntohs(clie_addr.sin_port));

            for(i = 0; i < FD_SETSIZE; i++)
                if(client[i] < 0)
                {
                    client[i] = connfd;//保存accept返回的文件描述符到client[]里
                    break;
                }
            //达到select能监控的文件个数上限1024
            if(i == FD_SETSIZE)
            {
                fputs("too many clients\n",stderr);
                exit(1);
            }

            FD_SET(connfd,&allset);//添加一个新的文件描述符到监控信号集里
            if(connfd > maxfd)
                maxfd = connfd;//select第一个参数需要
            if(i > maxi)
                maxi = i;//更新client[]最大下标值

            if(--nready == 0)
                continue;//如果没有更多的就绪文件描述符继续回到上面select阻塞监听，负责处理未处理完的就绪文件描述符

        }
        for(i = 0; i<= maxi; i++)//检测那个clients有数据就绪
        {
            if((sockfd = client[i]) < 0)
                continue;
            if(FD_ISSET(sockfd,&rset))
            {
                if((n = Read(sockfd,buf,MAXLINE)) == 0)
                {
                    //client关闭链接时，服务器端也关闭对应链接
                    Close(sockfd);
                    FD_CLR(sockfd,&allset);//解除select监控此文件描述符
                    client[i] = -1;
                }
                else
                {
                    int j;
                    for(j = 0;j < n;j++)
                        buf[j] = toupper(buf[j]);  
                    Write(sockfd,buf,n);
                }
                if(--nready == 0)
                    break;
            }
        }
    }
    Close(listenfd);
    return 0;
}
