#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    fd = open("123",O_CREAT);
    printf("%d\n",fd);
    return 0;
}
