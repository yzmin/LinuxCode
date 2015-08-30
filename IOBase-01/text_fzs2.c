#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MSG_TRY "try again\n"
#define MSG_TIMEOUT "timeout\n"

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}

int main(void)
{
    char buf[10];
    int fd,n,i;
    fd = open("/dev/tty",O_RDONLY|O_NONBLOCK);
    if(fd < 0)
    {
        sys_err("open /dev/tty");
    }
    for(i = 0; i < 5; i++)
    {
        n = read(fd,buf,10);
        if(n >= 0)
            break;
        if(errno != EAGAIN)
        {
            sys_err("read /dev/tty");
        }
        sleep(1);
        write(STDOUT_FILENO,MSG_TRY,strlen(MSG_TRY));
    }
    if(i == 5)
        write(STDOUT_FILENO,MSG_TIMEOUT,strlen(MSG_TIMEOUT));
    else
        write(STDOUT_FILENO,buf,10);

    close(fd);
    return 0;
}
