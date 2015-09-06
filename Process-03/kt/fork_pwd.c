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
        printf("kill child %d\n",wait(NULL));
    }
    else if(pid == 0)
    {
        printf("child\n");
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
