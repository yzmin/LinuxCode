#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    pid_t pid;

    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(1);
    }
    int num = atoi(argv[1]);

    while(num--)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
        if(pid < 0)
        {
            perror("fork fail");
            exit(-1);
        }
    }
    if(pid == 0)
    {
        printf("parentpid = %d, childpid = %d\n",getppid(),getpid());
    }
    if(pid > 0)
    {
        printf("parentpid = %d, pid = %d\n",getppid(),getpid());
        while(1);
    }

    return 0;
}
