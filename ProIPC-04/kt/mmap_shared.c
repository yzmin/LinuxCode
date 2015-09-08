#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    int fd,len,i = 0;
    char *mm;

    if((fd = open("abc",O_RDWR|O_CREAT,0777))< 0)
        sys_err("open");
    ftruncate(fd,4096);

    mm = (char*)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(mm == MAP_FAILED)
        sys_err("mmap");

    while(i < 4096)
    {
        *(mm+i) = 'a' + i;
        i++;
        sleep(1);
    }

    if(munmap(mm,4096) < 0)
    {
       sys_err("munmap");
    }
    close(fd);

    return 0;
}

