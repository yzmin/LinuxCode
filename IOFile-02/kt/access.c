#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }

    if(access(argv[1],F_OK) != 0)
    {
        int ret = creat(argv[1],0664);
        printf("argv[1] = %s ,%d F_OK\n",argv[1],ret);
    }
    return 0;
}
