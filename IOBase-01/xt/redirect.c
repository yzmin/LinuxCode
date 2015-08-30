#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    int fd;
    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }
    close(STDOUT_FILENO);
    fd = open(argv[1],O_RDWR);
    if(fd < 0)
       sys_err("open");
    printf("yzmin hello\n");

//    close(fd);


    return 0;
}
