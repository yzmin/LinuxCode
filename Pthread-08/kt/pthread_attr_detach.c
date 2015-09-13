#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *do_task(void *arg)
{
    int m = 20; 
    //pthread_detach(pthread_self());//第一种线程回收方式
    while(m--)
    {
        //printf("%x\n",(unsigned int)pthread_self());
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t tid;
    int err,i = 1,n = 100;
    //第二种，在线程创建之前，使用线程属性设置
    pthread_attr_t attr;
    pthread_attr_init(&attr);//默认属性
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//单独设置游离态
    pthread_attr_setstacksize(&attr,1024*1024*1);


    while(1)
    {
       err =  pthread_create(&tid,&attr,do_task,(void*)n);
       if(err != 0)
       {
           printf("err = %d \t %s\n",err,strerror(err));
           break;
       }
       printf("thread : %d\n",++i);
    }
    while(1)
    {
        printf("main thread\n");
        sleep(1);
    }
    return 0;
}
