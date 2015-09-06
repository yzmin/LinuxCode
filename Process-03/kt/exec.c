#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("%d\n",getpid());
    //     路径       //argv[0]占位
    //execl("/bin/ls","/bin/ls","-l",NULL);
    //execl("/bin/ls","yzmin","-l",NULL);
    //execl("b.out","b.out","hello","123",NULL);
    //execlp("ls","/bin/ls","-l",NULL);//表示使用环境变量
    //execl("b.out","b.out","-l",NULL);
    char *argvv[] = {"ls","-l",NULL};
    execv("/bin/ls",argvv);

    printf("world\n");

    return 0;
}
