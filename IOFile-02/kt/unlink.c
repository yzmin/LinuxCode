#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc,char *argv[])
{
    char buf[1024];
    int len;

    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }
    int fd = open(argv[1],O_CREAT | O_RDWR,0664);
    if(fd < 0)
        sys_err("open");
    unlink(argv[1]);
    write(fd,"helloworld",10);
    lseek(fd,0,SEEK_SET);
    len = read(fd,buf,sizeof(buf));
    buf[len] = '\n';
    write(STDOUT_FILENO,buf,len);
    while(1);
    close(fd);

    return 0;
}
    
