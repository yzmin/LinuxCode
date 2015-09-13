#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *do_task(void *arg)
{
    exit(0);
    while(1)
    {
        printf("%x\n",(unsigned int)pthread_self());
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t tid;
    int err,i = 1;

    while(1)
    {
       err =  pthread_create(&tid,NULL,do_task,NULL);
       if(err != 0)
       {
           printf("err = %d \t %s\n",err,strerror(err));
           break;
       }
       printf("thread : %d\n",++i);
    }
    return 0;
}
