#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

void deamon()
{
    pid_t pid;
    
    if((pid = fork()) < 0)
    {
        sys_err("fork");
    }
    else if(pid > 0)
    {
        exit(0);
    }
    setsid();
    if(chdir("/") < 0)
        sys_err("chdir");
    close(0);
    open("/dev/null",O_RDWR);
    dup2(0,1);
    dup2(0,2);
}

int main(void)
{
    deamon();
    int fd,len;
    time_t tm;
    char buf[1024];
    fd = open("/time.log",O_CREAT|O_WRONLY|O_APPEND,0644);
    while(1)
    {
        memset(buf,0,sizeof(buf));
        time(&tm);
        localtime(&tm);
        ctime_r(&tm,buf);
        len = strlen(buf);
        buf[len] = '\0';
        write(fd,buf,len);
        sleep(5);
    }
    return 0;
}
