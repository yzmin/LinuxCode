#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    if(pid > 0)
    {
        printf("parent\n");
        while(1);
    }
    else if(pid == 0)
    {
        char *buf[] = {"pwd",NULL};
        execvp("pwd",buf);
    }
    else
    {
        perror("fork");
        exit(1);
    }
    return 0;
}
