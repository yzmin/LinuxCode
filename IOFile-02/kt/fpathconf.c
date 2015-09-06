#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("%ld\n",pathconf("aa",_PC_NAME_MAX));

    return 0;
}
