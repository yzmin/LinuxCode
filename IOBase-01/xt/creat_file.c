#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc,char *argv[])
{
    int fd,len;
    char buf[512];
    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }
#if 0
    fd = open(argv[1],O_WRONLY | O_APPEND);
    fd = open(argv[1],O_CREAT | O_WRONLY | O_APPEND,0664);
    fd = open(argv[1],O_CREAT | O_WRONLY | O_TRUNC,0664);
#endif 
    fd = open(argv[1],O_CREAT | O_WRONLY | O_EXCL,0664);

    if(fd < 0)
        sys_err("open");

    len = read(STDIN_FILENO,buf,sizeof(buf));
    write(fd,buf,len);

    return 0;
}


