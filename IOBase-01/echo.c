#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{
    int len;
    char buf[512];
    len = read(STDIN_FILENO,buf,sizeof(buf));
    write(STDIN_FILENO,buf,len);
    return 0;
}
