#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    char buf[1024];

    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }
    int len = readlink(argv[1],&buf,sizeof(buf));
    buf[len] = '\0';
    printf("size:%d\t%s -> %s\n",len,argv[1],buf);

    return 0;
}

