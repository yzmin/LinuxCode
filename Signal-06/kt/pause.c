#include <stdio.h>
#include <signal.h>

void do_sig(int n)
{

}

int main(void)
{
    signal(SIGINT,do_sig);

    printf("hello\n");
    pause();
    printf("world\n");
}
