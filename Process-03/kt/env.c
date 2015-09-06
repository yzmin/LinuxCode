#include <stdio.h>

//int main(int argc,char *argv[],char *environ[])
int main(int argc,char *argv[])
{
    extern char **environ;
    int i = 0;
    while(environ[i] != NULL)
        printf("%s\n",environ[i++]);

    return 0;
}

