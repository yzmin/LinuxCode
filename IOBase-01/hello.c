#include <stdio.h>

int main(void)
{
    FILE *fp;
    fp = fopen("abc","w+");
    fprintf(fp,"hello\n");
    fflush(fp);
    //fclose(stdout);
    while(1)
        ;
/*
    while(1)
    {
        printf("hello");
        usleep(10000);
    }
    */
    return 0;
}
