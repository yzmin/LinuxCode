#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int i = 0;
    while(i < 1000)
    {
        pid = fork();
        if(pid == 0)
            break;
        else if(pid < 0)
        {
            perror("fork");
            exit(-1);
        }
        i++;
    }

    if(pid == 0)
    {
        int n;
        srand(time(NULL));
        n = rand()%10;
        while(n--)
        {
            printf("I am child %d\n",getpid());
            sleep(1);
        }
    }
    else if(pid > 0)
    {
        int wpid;
        while(1)
        {
            wpid = wait(NULL);//如果没有子进程结束，wait阻塞等待
#if 0
            if(wpid == -1)
                break;
#endif
            printf("wait for %d\n",wpid);
        }
    }

    return 0;
}

