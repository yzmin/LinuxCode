#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *do_task(void *arg)
{
    long long n = 0;
    while(1)
    {
        n++;
        pthread_testcancel();//可以产生一个系统调用
        //printf("child thread\n");
        //sleep(1); 
    }
    return NULL;
}

int main(void)
{
    pthread_t tid;
    char buf[1024];

    pthread_create(&tid,NULL,do_task,NULL);
    while(1)
    {
        fgets(buf,sizeof(buf),stdin);
        if(strcmp(buf,"bye\n") == 0)
        {
            pthread_cancel(tid);
            printf("bye child\n");
        }
        printf("main : %s\n",buf);
    }
    return 0;
}
