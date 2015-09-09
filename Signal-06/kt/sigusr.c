#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int num;
pid_t pid;

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

void do_sig_parent(int n)
{
    printf("p %d\n",num); 
    num += 2;
    sleep(1);
    kill(pid,SIGUSR1);//子进程还没执行，就发送信号了，所有子进程就终止了。
}

void do_sig_child(int n)
{
    printf("c %d\n",num); 
    num += 2;
    kill(getppid(),SIGUSR1);
}

int main(void)
{
    struct sigaction act;
    //SIGUSR1
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGUSR1);
    sigprocmask(SIG_BLOCK,&set,NULL);//阻塞

    if((pid = fork()) < 0)
    {
        sys_err("fork");
    }
    else if(pid == 0)
    {
        //child 
        act.sa_handler = do_sig_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGUSR1,&act,NULL);
        num = 2;
        sigprocmask(SIG_UNBLOCK,&set,NULL);//解除阻塞
        while(1)
        {
            sleep(1);
        }
    }
    else
    {
        //parent
        act.sa_handler = do_sig_parent;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGUSR1,&act,NULL);
        sigprocmask(SIG_UNBLOCK,&set,NULL);//解除阻塞
        num = 1;
        raise(SIGUSR1);
        while(1)
        {
            sleep(1);
        }
    }

    return 0;
}
