#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc,char *argv[])
{
    int fd,len;
    if(argc < 3)
    {
        printf("./a.out filename size\n");
        exit(-1);
    }
    fd = open(argv[1],O_CREAT | O_EXCL | O_RDWR,0644);
    len = atoi(argv[2]);
    if(fd < 0)
        sys_err("open");
    lseek(fd,len-1,SEEK_SET);
    write(fd,"\0",1);

    close(fd);
    return 0;
}
