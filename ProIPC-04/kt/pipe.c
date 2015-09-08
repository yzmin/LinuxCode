#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    int pfd[2],len,i = 0;
    char buf[1024];
    pid_t pid;

    if(pipe(pfd) < 0)
        sys_err("pipe");

    pid = fork();
    if(pid > 0)
    {
        //父进程关闭读端0
        close(pfd[0]);
        while(1)
        {
            sprintf(buf,"yzmin %d\n",i++);
            write(pfd[1],buf,strlen(buf));
            //read(pfd[0],buf,2);
            sleep(1);
        }

    }
    else if(pid == 0)
    {
        //子进程关闭写端1
        close(pfd[1]);
        while(1)
        {
            len = read(pfd[0],buf,sizeof(buf));
            write(STDOUT_FILENO,buf,len);
        }
    }
    else
    {
        sys_err("fork");
    }

#if 0
    //往管道的写端写入数据
    write(pfd[1],"hello",5);
    //从管道的读端读出数据
    len = read(pfd[0],buf,sizeof(buf));
    //写到标准输出上
    write(STDOUT_FILENO,buf,len);
#endif 

    return 0;
}
