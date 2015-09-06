#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int a[10];
    int i;
    srand(time(NULL));
    for(i = 0;i < 10; i++)
    {
        a[i] = rand()%10;
        printf("%d\n",a[i]);
    }
    return 0;
}
