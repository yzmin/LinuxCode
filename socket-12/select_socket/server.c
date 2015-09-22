#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <signal.h>
#include "wrap.h"

#define SERV_PORT 8090
#define MAXLINE 4096


int main(void)
{
    struct sockaddr_in serv_addr,clie_addr;
    int sfd,cfd,maxfd,res,len,i,j;
    fd_set rset,rbset;
    socklen_t clie_len;
    char buf[4096];

    sfd = Socket(AF_INET,SOCK_STREAM,0);

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);    

    Bind(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    Listen(sfd,128);

    FD_ZERO(&rbset);
    FD_SET(sfd,&rbset);//把用于接收客户端链接的sfd,设置到select中读监控集合
    maxfd = sfd;//最大文件描述符
    printf("Accept connect ...\n");
    while(1)
    {
        rset = rbset;
        res = select(maxfd+1,&rset,NULL,NULL,NULL);//返回活跃文件描述符
        if(res <= 0)
            continue; 
        if(FD_ISSET(sfd,&rset))//有客户端链接
        {
            clie_len = sizeof(clie_addr);
            cfd = Accept(sfd,(struct sockaddr *)&clie_addr,&clie_len);
            FD_SET(cfd,&rbset);
            maxfd = cfd;//扩大监听文件描述符范围
            res--;
        }
        //处理链接
        for(i = 0; (i <= maxfd) && (res > 0); i++)
        {
            if(FD_ISSET(i,&rset))
            {
               len = Read(i,buf,sizeof(buf)); 

                for(j = 0; j < len;j++)
                    buf[j] = toupper(buf[j]);
                
                Write(i,buf,len);
                res--;
            }
        }
    }

    return 0;
}
