#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void do_sig_child(int num)
{
    //信号不排队，进入到wait回收，但并发50个信号，也只处理一个
    //wait循环，则退出回调函数
    //printf("child  %d is over\n",wait(NULL));
    pid_t pid;
    //循环回收，僵尸进程
    while((pid = waitpid(0,NULL,WNOHANG)) > 0)
        printf("child %d is over\n",pid);
}

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    pid_t pid;
    int m = 100;
    while(m--)
    {
        if((pid = fork()) < 0)
        {
            sys_err("fork");
        }
        else if(pid == 0)
        {
            break;
        }
    }
   
    if(pid == 0)
    {
        //子进程结束发送了SIGCHLD信号
        int n = 5;
        while(n--)
        {
            printf("child %d\n",getpid());
            sleep(1);
        }
    }
    else
    {
        //捕捉 
        struct sigaction act;
        act.sa_handler = do_sig_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGCHLD,&act,NULL);

        //父进程自己干自己的事
        while(1)
        {
            printf("parent\n");
            sleep(1);
        }
    }

    return 0;
}
