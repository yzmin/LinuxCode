#include <stdio.h>
#include <unistd.h>

int main(void)
{
    while(1)
    {
        printf("%d\n",getpid());
        sleep(1);
    }
    return 0;
}
