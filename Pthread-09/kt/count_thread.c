#include <stdio.h>
#include <pthread.h>

#define N_LOOP 5000
int count;
//全局锁
pthread_mutex_t mutex;

void *do_it(void *arg)
{
    int i,val;
    for(i = 0; i < N_LOOP; i++)
    {
        pthread_mutex_lock(&mutex);//加锁
        //临界区
        val = count;
        printf("%x\t%d\n",(unsigned int)pthread_self(),val+1);
        count = val + 1;

        pthread_mutex_unlock(&mutex);//解锁
        //usleep(500);
    }
    return NULL;
}

int main(void)
{
    pthread_t tid1,tid2;
    //创建锁
    pthread_mutex_init(&mutex,NULL);//初始化锁
    
    pthread_create(&tid1,NULL,do_it,NULL);
    pthread_create(&tid2,NULL,do_it,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    pthread_mutex_destroy(&mutex);//销毁锁
    return 0;
}
