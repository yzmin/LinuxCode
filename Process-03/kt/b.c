#include <stdio.h>

int main(int argc,char *argv[])
{
    int i = 0;
    printf("%d\n",getpid());
    while(argv[i] != NULL)
    {
        printf("argv[%d] = %s\n",i,argv[i]);
    i++;
    }
    return 0;

}
