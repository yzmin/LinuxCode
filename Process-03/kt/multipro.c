#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int i;
    for(i = 0;i < 100; ++i)
    {
        pid = fork();
        if(pid == 0)
            break;
        else if(pid < 0)
        {
            perror("fail");
            exit(-1);
        }
    }
    if(pid == 0)
    {
        printf("child pid = %d,ppid = %d\n",getpid(),getppid());
    }
    if(pid > 0)
    {
        printf("parent pid = %d,ppid = %d\n",getpid(),getppid());
        while(1);
    }
    return 0;
} 
