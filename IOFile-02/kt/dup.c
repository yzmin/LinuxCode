#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
    int fd,fp;

    fd = dup(STDOUT_FILENO);//3
    close(STDOUT_FILENO);//1

    fp = open("abc",O_RDWR);//1
    write(STDOUT_FILENO,"hello\n",6);
    close(STDOUT_FILENO);//1

    dup(fd);//1
    write(fd,"world\n",6);
    
    return 0;
}
