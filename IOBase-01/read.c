#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc,char *argv[])
{
    int srcfd,destfd,len;
    char buf[4096];

    if(argc < 3)
    {
        printf("./mycp srcname destname\n");
        exit(-1);
    }
    srcfd = open(argv[1],O_RDONLY);
    if(srcfd < 0)
    {
        sys_err("open src");
    }
    destfd = open(argv[2],O_CREAT | O_WRONLY | O_TRUNC,0664);
    if(destfd < 0)
    {
        sys_err("open dest");
    }
    while((len = read(srcfd,buf,sizeof(buf))) > 0)
        write(destfd,buf,len);

    close(srcfd);
    close(destfd);

    return 0;
}
