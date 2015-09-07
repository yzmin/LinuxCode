#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if(pid > 0)
    {
        pid_t pid;
        pid = fork();
        if(pid > 0)
        {
            printf("ppid %d, pid %d\n",getppid(),getpid());
            while(1);
        }
        else if(pid == 0)
        {
            printf("ppid %d, pid %d\n",getppid(),getpid());
            while(1);
        }
        else
        {
            perror("fork");
            exit(-1);
        }
    }
    else if(pid == 0)
    {
        pid_t pid;
        pid = fork();
        if(pid > 0)
        {
            printf("ppid %d, pid %d\n",getppid(),getpid());
            while(1);
        }
        else if(pid == 0)
        {
            printf("ppid %d, pid %d\n",getppid(),getpid());
            while(1);
        }
        else
        {
            perror("fork");
            exit(-1);
        }
    }
    else
    {
        perror("fork");
        exit(-1);
    }

    return 0;
}
