#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(void)
{
    int pfd[2],len;
    pid_t pid;
    char buf[4096];

    if(pipe(pfd) < 0)
        sys_err("pipe");

    if((pid = fork()) < 0)
        sys_err("fork");
    else if(pid > 0)
    {
        //in parent
        close(pfd[0]);
        while(1)
        {
            len = read(STDIN_FILENO,buf,sizeof(buf));
            write(pfd[1],buf,len);
        }
        close(pfd[1]);

    }
    else 
    {
        //in child
        close(pfd[1]);
        int flags;
        int fd = open("abc",O_CREAT|O_RDWR,0766);
        if(fd < 0)
            sys_err("open");
        flags = fcntl(pfd[0],F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(pfd[0],F_SETFL,flags);
        while(1)
        {
            len = read(pfd[0],buf,sizeof(buf));
            if(len < 0)
            {
                printf("no word\n");
                sleep(1);
                continue;
            }
            write(fd,buf,len);
        }
        close(pfd[1]);
        close(fd);
    }
    return 0;
}
