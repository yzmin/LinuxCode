#include <stdio.h>
#include <pthread.h>

void *do_fun(void *arg)
{
    int num = (int)arg;
    while(1)
    {
        printf("child pid = %d tid = %x arg = %d\n",getpid(),(unsigned int)pthread_self(),num);
        sleep(1);
    }
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid,NULL,do_fun,(void *)5);
    while(1)
    {
        printf("main pid = %d tid = %x\n",getpid(),(unsigned int)pthread_self());
        sleep(1);
    }
    return 0;
}
