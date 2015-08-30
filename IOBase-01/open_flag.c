#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <errno.h> 

void sys_err(char *str) 
{ 
    perror(str);
    exit(-1);
}

int main(int argc,char **argv)
{
    close(1);
    int fd;
    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }
    printf("begin errno:%d\n",errno);
    fd = open(argv[1],O_RDWR);
    if(fd < 0)
    {
        printf("after errno:%d\n",errno);
        perror("open");//打印出错的信息
        exit(-1);
    }
    printf("suceess fd = %d\n",fd); //stdout -> STDOUT_FILENO -> 1
#if 0
    fd = open(argv[1],O_TRUNC);
#endif 

#if 0
    fd = open(argv[1],O_CREAT | O_EXCL,0664);
    if(fd < 0)
    {
        printf("open fail\n");
        exit(-1);
    }
    printf("do something\n");
#endif 
    close(fd);
    return 0;
}

