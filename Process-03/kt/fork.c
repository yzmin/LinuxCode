#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int i = 0;

    pid = fork();

    if(pid > 0)
    {
        while(1)
        {
            printf("%d I am parent %d,my parent is %d,child is %d\n",i+=2,getpid(),getppid(),pid);
            sleep(1);
        }
    }
    else if(pid == 0)
    {
        while(1)
        {
            printf("%d I am child %d,my parent is %d\n",i++,getpid(),getppid());
            sleep(1);
        }
    }
    else
    {
        perror("fork");
        exit(-1);
    } 
    return 0;
}
