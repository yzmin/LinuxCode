#include <stdio.h>
#include "mymath.h"

int main(void)
{
    int a = 6;
    int b = 3;
    printf("a + b = %d\n",add(a,b));
    printf("a - b = %d\n",sub(a,b));
    printf("a * b = %d\n",mul(a,b));
    printf("a / b = %d\n",dive(a,b));
    return 0;
}
