#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MSG_TRY "try again\n"

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}

int main(void)
{
    char buf[10];
    int fd,n;
    fd = open("/dev/tty",O_RDONLY|O_NONBLOCK);
    if(fd < 0)
    {
       sys_err("open /dev/tty");
    }
tryagain:
    n = read(fd,buf,10);
    if(n < 0)
    {
        if(errno == EAGAIN)
        {
            sleep(1);
            write(STDOUT_FILENO,MSG_TRY,strlen(MSG_TRY));
            goto tryagain;
        }
        sys_err("read /dev/tty");
    }
    write(STDOUT_FILENO,buf,n);
    close(fd);
    return 0;
}
