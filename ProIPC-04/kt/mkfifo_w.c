#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    int fd;
    int n = 5;
    char buf[1024];
    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(1);
    }
    if(access(argv[1],F_OK))
        if(mkfifo(argv[1],0777) < 0)
            sys_err("mkfifo");

    printf("begin open\n");
    if((fd = open(argv[1],O_WRONLY)) < 0)
        sys_err("open");
    printf("after open\n");

    while(n--)
    {
        sprintf(buf,"yzmin %d\n",n);
        write(fd,buf,strlen(buf));
        sleep(1);
    }
    close(fd);

    return 0;
}
