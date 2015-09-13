#include <stdio.h>
#include <pthread.h>

struct STU
{
    int id;
    char str[128];
};

void *do_task(void *arg)
{
    struct STU *s = (struct STU *)arg;

    char name[256] = "yzmin";
    printf("%p\t%s\n",name,name);
    printf("%d\t%s\n",s->id,s->str);

    return (void*)name;
}

int main(void)
{
    pthread_t tid;
    char *status;
    struct STU s1 = {12,"xiaoqiong"};
    
    pthread_create(&tid,NULL,do_task,(void*)&s1);
    pthread_join(tid,(void **)&status);//等待子线程结束回收,阻塞
    printf("status = %p\n",status);//status -> name
    printf("%s\n",status);
    return 0;
}
