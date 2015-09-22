#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

struct mt 
{
    int num;
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;
};

int main(void)
{
    int fd,i;
    struct mt *mm;
    pid_t pid;
    fd = open("m_test",O_CREAT | O_RDWR,0777);
    ftruncate(fd,sizeof(*mm));
    mm = mmap(NULL,sizeof(*mm),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    memset(mm,0,sizeof(*mm));

    pthread_mutexattr_init(&mm->mutexattr);
    pthread_mutexattr_setpshared(&mm->mutexattr,PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&mm->mutex,&mm->mutexattr);

    pid = fork();
    if(pid == 0)
    {
        for(i = 0; i < 10; i++)
        {
            pthread_mutex_lock(&mm->mutex);
            (mm->num)++;
            printf("num++:%d\n",mm->num);
            pthread_mutex_unlock(&mm->mutex);
            sleep(1);
        }
    }
    else if(pid > 0)
    {
        for(i = 0; i < 10; i++)
        {
            pthread_mutex_lock(&mm->mutex);
            mm->num += 2;
            printf("num+=2:%d\n",mm->num);
            pthread_mutex_unlock(&mm->mutex);
            sleep(1);
        }
        wait(NULL);
    }
    pthread_mutex_destroy(&mm->mutex);
    pthread_mutexattr_destroy(&mm->mutexattr);

    munmap(mm,sizeof(*mm));
    unlink("mt_test");

    return 0;
}
