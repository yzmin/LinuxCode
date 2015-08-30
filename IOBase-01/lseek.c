#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    int fd,len;
    char buf[1024];
    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }
    fd = open(argv[1],O_CREAT | O_RDWR,0664);
    write(fd,"hello",5);
    lseek(fd,0,SEEK_SET);
    read(fd,buf,sizeof(buf));
    printf("%s\n",buf);
    //write(STDOUT_FILENO,buf,5);

#if 0
    fd = open(argv[1],O_RDONLY);
    len = lseek(fd,0,SEEK_END);
    printf("len = %d\n",len);
#endif
    close(fd);
    return 0;
}

