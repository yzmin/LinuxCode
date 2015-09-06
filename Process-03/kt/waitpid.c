#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

//./a.out 3 ls -l
int main(int argc,char *argv[])
{
    pid_t pid;
    if(argc < 3)
    {
        printf("./a.out num ...\n");
        exit(-1);
    }
    int n = atoi(argv[1]);

    while(n--)
    {
        if((pid = fork()) == 0)
            break;
        else if (pid < 0)
            sys_err("fork");
    }
    if(pid == 0)
    {
        printf("I am %d,start %s ...\n",getpid(),argv[2]);
        execvp(argv[2],argv+2);
    }
    if(pid > 0)
    {
        int wpid,i = 0;
        //waitpid 返回值 -1:出错，没有子进程。 0:有子进程，但是子进程没有终止，非阻塞
        while((wpid = waitpid(-1,NULL,WNOHANG)) >= 0)
        {
            if(wpid == 0)
            {
                printf("wait for child %d\n",i++);
            }
            else
            {
                printf("child %d is over\n",wpid);
            }
            sleep(1);
        }
        if((wpid < 0) && (errno == ECHILD))
        {
            printf("all childs is over, bye\n");
        }
    }

}
