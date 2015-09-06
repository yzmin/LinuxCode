#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("./a.out filename size\n");
        exit(-1);
    }
    int size = atoi(argv[2]);

    if(access(argv[1],F_OK) != 0)
        creat(argv[1],0664);

    if(truncate(argv[1],size) < 0)
        sys_err("truncate");

    return 0;
}
