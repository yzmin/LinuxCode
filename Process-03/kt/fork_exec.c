#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        execl("b.out","b.out","yzmin","123456",NULL);
        while(1)
        {
            printf("child\n");
            sleep(1);
        }
    }
    else if(pid > 0)
    {
        while(1)
        {
            printf("parent\n");
            sleep(1);
        }
    }
    else
    {
        perror("fork fail");
        exit(-1);
    }
    return 0;
}
