#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void do_sigint(int num)
{
    printf("%d   hello world\n",num);
}

int main(void)
{
    struct sigaction act;
    //struct sigaction *act;
    //init struct act
    act.sa_handler = do_sigint;
    //act.sa_handler = SIG_IGN;//忽略捕捉
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGINT,&act,NULL);
    while(1)
    {
        printf("------------------------\n");
        sleep(1);
    }

    return 0;
}
