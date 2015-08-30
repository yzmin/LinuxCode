#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    int fd,len;
    if(argc < 3)
    {
        printf("./a.out filename size\n");
        exit(1);
    }
    fd = open(argv[1],O_CREAT | O_WRONLY |O_TRUNC,0644);
    len = atoi(argv[2]);
    lseek(fd,len-1,SEEK_END);
    write(fd,"\0",1);

    close(fd);
    return 0;
}
