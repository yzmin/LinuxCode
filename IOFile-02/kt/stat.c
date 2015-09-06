#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc,char *argv[])
{
    struct stat buf;

    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }
    if(stat(argv[1],&buf) < 0)
        sys_err("stat");

    if(S_ISREG(buf.st_mode))
        printf("-");
    else if(S_ISDIR(buf.st_mode))
        printf("d ");

    printf("%s : %d\n",argv[1],(int)buf.st_size);

    return 0;
}
    
