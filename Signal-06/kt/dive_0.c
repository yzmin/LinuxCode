#include <stdio.h>

int main(void)
{
    char *str = "hello";
    *str = 'H';
    printf("%s\n",str);
    //printf("%d\n",4 / 0);
    return 0;
}
