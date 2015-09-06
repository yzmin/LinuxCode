#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char a[] = "100";
    char b[] = "100";
    char c[] = "0x11";

    int x,y,z;
    x = strtol(a,NULL,10);
    y = strtol(b,NULL,2);
    z = strtol(c,NULL,16);

    printf("x = %d\n",x);
    printf("y = %d\n",y);
    printf("z = %d\n",z);
    
    return 0;
}
