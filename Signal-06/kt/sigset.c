#include <stdio.h>
#include <signal.h>

int main(void)
{
    printf("%ld\n",sizeof(sigset_t));
    return 0;
}
