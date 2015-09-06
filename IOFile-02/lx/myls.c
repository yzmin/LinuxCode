#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc,char *argv[])
{
    struct stat buf;

    if(argc < 2)
    {
        printf("./a.out filename\n");
        exit(-1);
    }

    if(stat(argv[1],&buf) == -1)
        sys_err("stat");

    if(S_ISDIR(buf.st_mode))
        printf("d");
    else
        printf("-");
    
    if(buf.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");
    
    if(buf.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");

    if(buf.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");
#if 0
    printf("\t%d",buf.st_nlink);
    printf("\t%d",buf.st_uid);
    printf("\t%d",buf.st_gid);
    printf("\t%d",buf.st_size);
    printf("\t%s\t",buf.st_atime);
#endif

    return 0;
}
