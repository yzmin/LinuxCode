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
    int fd,len;
    char *mm;

    if((fd = open("abc",O_RDWR))< 0)
        sys_err("open");
    len = lseek(fd,0,SEEK_END);

    mm = (char*)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(mm == MAP_FAILED)
        sys_err("mmap");

    printf("%s\n",mm);
    char *pbak = mm;
    while(*mm != '\0')
    {
        *mm = toupper(*mm);
        mm++;
    }

    if(munmap(pbak,len) < 0)
    {
       sys_err("munmap");
    }
    close(fd);

    return 0;
}

