#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *do_task(void *arg)
{
    int n = 5;
    while(n--)
    {
        printf("%x\n",pthread_self());
        sleep(1);
    }
    return (void *)3;
}

int main(void)
{
    pthread_t tid;
    int err,*status;
    pthread_create(&tid,NULL,do_task,NULL);
    //sleep(5);
    pthread_detach(tid);//设置子线程为分离态/游离态

    sleep(2);
    while(1)
    {
        err = pthread_join(tid,(void *)&status);
        if(err != 0)
        {
            printf("yzm %s\n",strerror(err));
            break;
        }
        else 
        {
            printf("child exit %ld\n",(long)status);
        }
    }
    return 0;
}
