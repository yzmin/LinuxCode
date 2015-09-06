#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char buf[1024];
    getcwd(buf,sizeof(buf));
    printf("%s\n",buf);

    creat("sss",0777);
    chdir("/");
    creat("abcd",0777);

    getcwd(buf,sizeof(buf));
    printf("%s\n",buf);

    return 0;
}
