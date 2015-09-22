#include <stdio.h>

int main(void)
{
    char buf[5];
    //while(1)
    {
        fgets(buf,sizeof(buf),stdin);
        printf(buf);
    }

    return 0;
}
