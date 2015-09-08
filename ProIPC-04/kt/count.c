#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int n = 0;
    pid_t pid;

    pid = fork();
    if(pid > 0)
    {
        /*in parent*/
        n = 1;
        while(1)
        {
            sleep(1);
            printf("parent %d\n",n);
            n+=2;
        }
    }
    else if(pid == 0)
    {
        /*in child*/
        while(1)
        {
            /*n++ ? n+=2*/
            printf("child %d\n",n);
            sleep(1);
            n+=2;
        }

    }
    else
    {
        perror("fork");
        exit(1);
    }
    return 0;
}
