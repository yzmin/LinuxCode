#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        printf("child id %d,group id %d\n",getpid(),getpgid(0));
        sleep(5);
        printf("child is %d,group id %d\n",getpid(),getpgid(0));
        exit(0);

    }
    else if(pid > 0)
    {
        printf("parent id %d,group id %d\n",getpid(),getpgid(0));
        sleep(1);
        setpgid(pid,pid);
        printf("parent id %d,group id %d\n",getpid(),getpgid(0));
        sleep(5);
    }
    else
    {
        return -1;
    }
    return 0;
}
