#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc,char *argv[])
{
    int fd;
    struct stat buf;
    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }
    fd = open(argv[1],O_RDWR);
    if(fd < 0)
        sys_err("open");

    fstat(fd,&buf);

    printf("%s : %d\n",argv[1],(int)buf.st_size);

    return 0;
}

