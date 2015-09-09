#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int count = 0;
    alarm(1);//设定定时器
    while(1)
    {
        printf("%d ",++count);
    }
    return 0;
}
