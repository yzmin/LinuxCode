#include <stdio.h>
#include <signal.h>

void sig_alarm(int signo)
{

}

unsigned int mysleep(unsigned int nsecs)
{
    struct sigaction newact,oldact;
    unsigned int unslept;
    sigset_t newmask,oldmask,suspmask;

    newact.sa_handler = sig_alarm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM,&newact,&oldact);

    //设置阻塞集
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGALRM);
    sigprocmask(SIG_BLOCK,&newmask,&oldmask);

    alarm(nsecs);//定时器一直在运行，即使没有CPU
    //挂起
    //临时解除阻塞集
    suspmask = oldmask;
    sigdelset(&suspmask,SIGALRM);
    sigsuspend(&suspmask);//挂起，临时解除阻塞集，恢复原来阻塞集

    unslept = alarm(0);
    sigaction(SIGALRM,&oldact,NULL);

    return unslept;
}

int main(void)
{
    printf("hello\n");
    mysleep(1);
    printf("world\n");
    return 0;
}
