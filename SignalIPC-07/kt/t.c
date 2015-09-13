#include <stdio.h>

int main(void)
{
    int n = 10;
    while(n != 10)//n 被编译器优化了
    {
        printf("hello\n");
        sleep(1);
    }
    return 0;
}
