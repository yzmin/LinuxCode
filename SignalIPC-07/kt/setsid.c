#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    if(pid > 0)
    {
        while(1)
            ;
        exit(0);
    }
    else if(pid == 0)
    {
        setsid();
        while(1)
        {
            system("ls");
            sleep(1);
        }
    }
    return 0;
}
