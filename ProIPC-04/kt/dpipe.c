#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}

int main(void)
{
    int pfd1[2];
    int pfd2[2];
    int pi1 = pipe(pfd1);
    int pi2 = pipe(pfd2);
    char buf[1024];
    int len,i = 0;
    if((pi1<0)||(pi2<0))
    {
        sys_err("pipe fail");
    }
    pid_t pid;
    pid = fork();
    if(pid > 0)
    {
        while(1)
        {
            //父读子写
            len = read(pfd2[0],buf,sizeof(buf));
            write(STDOUT_FILENO,buf,len);
            sleep(2);
            //父写子读
            sprintf(buf,"parent send yzmin %d\n",i++);
            write(pfd1[1],buf,strlen(buf));
            sleep(2);
        }
    }
    else if(pid == 0)
    {
        int flags;
        while(1)
        {
            flags = fcntl(pfd1[0],F_GETFL);
            flags |= O_NONBLOCK;
            fcntl(pfd1[0],F_SETFL,flags);
            //子读父写
            len = read(pfd1[0],buf,sizeof(buf));
            write(STDOUT_FILENO,buf,len);
            sleep(3);
            //子写父读
            sprintf(buf,"child send hello %d\n",i++);
            write(pfd2[1],buf,strlen(buf));
            sleep(3);
        }
    }
    else 
    {
        sys_err("fork");
    }
    return 0;
}
