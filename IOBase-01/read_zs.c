#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}
#if 0
int main(int argc, char *argv[])
{
    int fd,len;
    char buf[4096];
    while(1)
    {
        len = read(STDIN_FILENO,buf,sizeof(buf));
        printf("hello\n");
        write(STDOUT_FILENO,buf,len);
    }
    return 0;
}
#endif 

int main(int argc,char *argv[])
{
    int len;
    char buf[5];
    len = read(STDIN_FILENO,buf,sizeof(buf));
    write(STDOUT_FILENO,buf,len);

    return 0;
}
