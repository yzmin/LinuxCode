#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

#define PARENT_HAND 1
#define CHILD_HAND 2

struct ITERM
{
    int flag;
    char buf[1024];
};

int main(void)
{
    pid_t pid;
    struct ITERM *mm;
    int fd,i = 0;

    fd = open("tmpfile",O_CREAT|O_RDWR,0777);
    ftruncate(fd,4096);

    //mm = (struct ITERM*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    mm = (struct ITERM*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
    mm->flag = PARENT_HAND;
    close(fd);
    unlink("tmpfile");

    pid = fork();
    if(pid > 0)
    {
        while(1)
        {
//            if(mm->flag == PARENT_HAND)
            {
                sprintf(mm->buf,"yzmin %d\n",i++);
                mm->flag = CHILD_HAND;
                printf("p %s\n",mm->buf);
            }
            sleep(1);
        }
        munmap(mm,4096);
    }
    else if(pid == 0)
    {
        while(1)
        {
            //if(mm->flag == CHILD_HAND)
            {
                printf("%s\n",mm->buf);
                mm->flag = PARENT_HAND;
            }
            sleep(1);
        }
        munmap(mm,4096);
    }
    else 
    {
        perror("fork");
        exit(1);
    }
    return 0;
}
