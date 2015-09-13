#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("fd 0: %s\n",ttyname(0));
    printf("fd 1: %s\n",ttyname(1));
    return 0;
}
