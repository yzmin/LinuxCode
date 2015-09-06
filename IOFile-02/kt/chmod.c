#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }

    if(chmod(argv[1],0777)!= 0)
    {
        sys_err("chmod");
    }

    return 0;
}
