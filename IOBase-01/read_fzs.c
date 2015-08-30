#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

void sys_err(char *str)
{
    perror(str);
    //exit(-1);
}
int main(int argc,char *argv[])
{
    int len,i = 0;
    char buf[50];
    //1、STDIN_FILENO默认是阻塞属性
    close(STDIN_FILENO);
    //2、open得到新的文件描述符为0,即STDIN_FILENO,设置了非阻塞属性
    open("/dev/tty",O_RDONLY|O_NONBLOCK);
    while(1)
    {
        len = read(STDIN_FILENO,buf,sizeof(buf));
        if(len > 0)
        {
            if(strncmp("yes",buf,3) == 0)
            {
                printf("ok\n");
                break;
            }
        }
        write(STDOUT_FILENO,buf,len);
        sleep(1);
        printf("%d\n",i++);
    }

    return 0;
}
