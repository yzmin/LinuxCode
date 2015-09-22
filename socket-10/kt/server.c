#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PROT 8080

int main(void)
{
    int sfd,cfd,clen,len,i;
    struct sockaddr_in saddr, caddr;
    char ipstr[128],buf[4096];

    sfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&saddr,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);//任意本地ip地址
    saddr.sin_port = htons(SERV_PROT);

    bind(sfd,(struct sockaddr *)&saddr,sizeof(saddr));
    listen(sfd,20);

    clen = sizeof(caddr);
    cfd = accept(sfd,(struct sockaddr *)&caddr,&clen);//阻塞，等待客户端链接

    printf("client ip = %s\tport = %d\n",inet_ntop(AF_INET,(void *)&caddr.sin_addr.s_addr,ipstr,sizeof(ipstr)),ntohs(caddr.sin_port));

    len = read(cfd,buf,sizeof(buf));
    //小写转大写
    for(i = 0;i < len; i++)
        buf[i] = toupper(buf[i]);

    write(cfd,buf,len);

    close(cfd);
    close(sfd);

    return 0;
}
