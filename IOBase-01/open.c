#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    int fd,i = 3;
    char name[100];
    while(1)
    {
        sprintf(name,"file%d",i);
        fd = open(name,O_CREAT,0664);
        if(fd <0)
            break;
        printf("%d\n",fd);
        i++;
    }
    return 0;
}
