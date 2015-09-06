#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char buf[4096];
    printf("%s\n",getenv("PATH"));

    char *str = getenv("PATH");
    getcwd(buf,sizeof(buf));
    /*
       1. str -> buf 后  正确的
       2. buf -> str 后
       3. 都可以
    */
    strcat(buf,":");
    strcat(buf,str);

    setenv("PATH",buf,1);// 1 表示覆盖
    printf("%s\n",getenv("PATH"));

    return 0;
}
