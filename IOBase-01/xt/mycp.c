#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc,char *argv[])
{
    int srcfd,destfd,len;
    char buf[1024];
    if(argc < 3)
    {
        printf("./a.out filename1 filename2\n");
        exit(-1);
    }
    srcfd = open(argv[1],O_RDONLY);
    if(srcfd < 0)
        sys_err("open strfd");
    destfd = open(argv[2],O_CREAT | O_WRONLY,0664);
    if(destfd < 0)
        sys_err("open destfd");


    while((len = read(srcfd,buf,sizeof(buf))) > 0)
        write(destfd,buf,len);

    close(srcfd);
    close(destfd);

    return 0;
}
