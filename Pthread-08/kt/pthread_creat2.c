#include <stdio.h>
#include <pthread.h>

pthread_t tid;

void *do_fun(void *arg)
{
    int num = (int)arg;
    //pthread_self()直接去当前线程PCB里获得线程id
    //如果此时主控线程的pthread_creat还没调用返回，有可能tid此时还为0
    if(tid != pthread_self())
        printf("hello");

    while(1)
    {
        printf("child pid = %d tid = %x arg = %d\n",getpid(),(unsigned int)pthread_self(),num);
        sleep(1);
    }
}

int main(void)
{
    //1.创建线程 2.保存线程id到tid 3.返回
    pthread_create(&tid,NULL,do_fun,(void *)5);
    while(1)
    {
        printf("main pid = %d tid = %x\n",getpid(),(unsigned int)pthread_self());
        sleep(1);
    }
    return 0;
}
