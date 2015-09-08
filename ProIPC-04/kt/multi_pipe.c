#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    pid_t pid;
    int pfd[2];
    char buf[1024];
    int len;

    if(pipe(pfd) < 0)
        sys_err("pipe");

    pid = fork();
    if(pid > 0)
    {
        close(pfd[0]);
        sprintf(buf,"yzmin parent ppid %d,pid %d\n",getppid(),getpid());
        write(pfd[1],buf,strlen(buf));
        close(pfd[1]);


    }
    else if(pid == 0)
    {
        pid = fork();
        if(pid == 0)
        {
            close(pfd[0]);
            sprintf(buf,"sun write ppid %d,pid %d\n",getppid(),getpid());
            write(pfd[1],buf,strlen(buf));
            close(pfd[1]);
            exit(0);
        }
        else if(pid > 0)
        {
            close(pfd[1]);
            sleep(3);
            len = read(pfd[0],buf,sizeof(buf));
            write(STDOUT_FILENO,buf,len);
            exit(1);
        }
        else 
        {
            sys_err("fork");
        }
    }
    else
    {
        sys_err("fork");
    }
    wait(NULL);
    return 0;

}
