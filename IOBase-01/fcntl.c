#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#if 0
int main(void)
{
    int status;
    int fd = open("abc",O_CREAT | O_WRONLY,0754);
    if(fd < 0)
        perror("open");

    status = fcntl(fd,F_GETFL);
    if(status & O_RDONLY)
        printf("O_RDONLY\n");
    else if(status & O_RDWR)
        printf("O_RDWR\n");
    else if(status & O_WRONLY)
        printf("O_WRONLY\n");

    close(fd);
    return 0;
}
#endif

int main(void)
{
    int status,len;
    char buf[1024];

    //fcntl获取和设置文件描述符的访问控制属性
    status = fcntl(STDIN_FILENO,F_GETFL);//获取
    status |= O_NONBLOCK;
    fcntl(STDIN_FILENO,F_SETFL,status);//设置
    while(1)
    {
        len = read(STDIN_FILENO,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,len);
        printf("hello\n");
        sleep(1);
    }
    return 0;
}
