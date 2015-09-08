#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
    int fd,len;
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

    if((fd = open(argv[1],O_RDONLY)) < 0)
        sys_err("open");

    while(1)
    {
        len = read(fd,buf,sizeof(buf));
        if(len < 0)
        {
            sys_err("read");
            break;
        }
        write(STDOUT_FILENO,buf,len);
    
    }
    close(fd);

    return 0;
}
