#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <signal.h>
#include "wrap.h"

#define SERV_IP "192.168.152.128"
#define SERV_PORT 8090
#define MAXLINE 4096

//捕捉函数
void do_sigchild(int num)
{
    pid_t cpid;
    while((cpid = waitpid(0,NULL,WNOHANG)) > 0)
    {
#ifdef DEBUG
        printf("child %d\n is over\n",cpid);
#else
        ;
#endif
    }
}

int main(void)
{
    int sfd,cfd,len,i;
    char buf[MAXLINE],clie_ip[128];
    pid_t pid;
    struct sigaction act;

    struct sockaddr_in serv_addr,clie_addr;
    socklen_t clie_len;

    sfd = Socket(AF_INET,SOCK_STREAM,0);

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(SERV_PORT);

    Bind(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    Listen(sfd,128);
    //信号捕捉设置
    act.sa_handler = do_sigchild;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD,&act,NULL);

    while(1)
    {
        clie_len = sizeof(clie_addr);
        cfd = Accept(sfd,(struct sockaddr *)&clie_addr,&clie_len);
        printf("recive client %s\t%d connect\n",inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,clie_ip,sizeof(clie_ip)),ntohs(clie_addr.sin_port));

        pid = fork();
        if(pid == 0)
        {
            //child
            Close(sfd); 
            while(1)
            {
                len = Read(cfd,buf,sizeof(buf));//阻塞
                if(len == 0)
                {
                    printf("client %s is close connect\n",inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,clie_ip,sizeof(clie_ip)));
                    Close(cfd);
                    exit(1); 
                }

                for(i = 0;i < len; i++)
                    buf[i] = toupper(buf[i]);

                Write(cfd,buf,len);
            }
        }
        else if(pid > 0)
        {
            //parent
            Close(cfd);//父进程不干活，子进程负责通信
        }
        else 
        {
            perr_exit("fork err");
        }
    }
    Close(sfd);

    return 0;
}
