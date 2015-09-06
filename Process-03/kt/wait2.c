#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int status;

    pid = fork();
    if(pid > 0)
    {
        printf("yzmin\n");
        printf("kill child %d\n",waitpid(0,&status,WNOHANG));
        if(WIFEXITED(status))
            printf("exit status %d\n",WEXITSTATUS(status));

        if(WIFSIGNALED(status))
            printf("exit status %d\n",WTERMSIG(status));

        printf("world\n");
    }
    else if(pid == 0)
    {
        while(1)
        {
            printf("hello\n");
            sleep(1);
//            return 2;
        }
    }
    else
    {
        perror("fork");
        exit(1);
    }
    return 0;
}
