#include <stdio.h>
#include <signal.h>

void print_pend(sigset_t pset)
{
    int i;
    for(i = 1; i < 32; i++)
    {
        if(sigismember(&pset,i) == 1)
        {
            putchar('1');
        }
        else 
        {
            putchar('0');
        }
    }
    puts(" ");
}

int main(void)
{
    int n = 10;
    sigset_t set,pset;

    sigemptyset(&set);
    sigaddset(&set,SIGINT);//这步没有设置阻塞，只是构造一个信号集
    sigaddset(&set,SIGQUIT);
    sigaddset(&set,SIGKILL);//不能阻塞该信号
    sigprocmask(SIG_BLOCK,&set,NULL);//把构造好set设置为当前进程的阻塞信号集

    while(1)
    {
        sigpending(&pset);//获取当前进程未决信号集
        print_pend(pset);
        sleep(1);
        if(n == 0)
        {
            sigemptyset(&set);
            sigaddset(&set,SIGINT);
            sigprocmask(SIG_UNBLOCK,&set,NULL);//把构造好set设置为当前进程的阻塞信号集,mask &= ~set
        }
        n--;
    }

    return 0;
}
