#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    DIR *dp;//目录项指针
    struct dirent *dirp;//每条目录项结构体

    dp = opendir(".");//打开当前目录

    if(!dp)
        sys_err("opendir");

    while(dirp = readdir(dp))//读取当前目录项
    {
        printf("inode = %d\tname = %s\n",(int)dirp->d_ino,dirp->d_name);
    }

    closedir(dp);
    return 0;
}


