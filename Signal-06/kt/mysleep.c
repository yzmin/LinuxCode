#include <stdio.h>
#include <signal.h>

void sig_alarm(int signo)
{

}

unsigned int mysleep(unsigned int nsecs)
{
    struct sigaction newact,oldact;
    unsigned int unslept;

    newact.sa_handler = sig_alarm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM,&newact,&oldact);

    //当执行完这条语句之后，CPU的时间用完了，定时器时间到了，触发了捕捉函数，然后得到CPU，挂起进程，没有信号唤醒该进程了。时序竞态
    alarm(nsecs);//定时器一直在运行，即使没有CPU
    //挂起
    pause();

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
