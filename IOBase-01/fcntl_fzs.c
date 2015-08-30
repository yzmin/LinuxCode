#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MSG_TRY "try again\n"

int main(void)
{
    char buf[10];
    int n;
    int flags;
    flags = fcntl(STDIN_FILENO,F_GETFL);
    flags |= O_NONBLOCK;
    if(fcntl(STDIN_FILENO,F_SETFL,flags) == -1)
    {
        perror("fcntl");
        exit(-1);
    }
tryagain:
    n = read(STDIN_FILENO,buf,10);
    if(n < 0)
    {
        if(errno == EAGAIN)
        {
            sleep(1);
            write(STDOUT_FILENO,MSG_TRY,strlen(MSG_TRY));
            goto tryagain;
        }
        perror("read stdin");
        exit(1);
    }
    write(STDOUT_FILENO,buf,n);
    return 0;
}
