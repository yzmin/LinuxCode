#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define LEN 4096

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(int argc,char *argv[])
{
    int srcfd,destfd;
    int size;
    char *mm;
    if(argc < 3)
    {
        printf("./a.out src dest\n");
        exit(-1);
    }
    if(!access(argv[1],F_OK))
    {
        srcfd = open(argv[1],O_RDONLY);
        size = lseek(srcfd,0,SEEK_END);
    }
    else 
    {
        printf("srcfile bu cunzai\n");
        exit(1);
    }
    if(srcfd < 0)
        sys_err("open src");

    if(!access(argv[2],F_OK))
        destfd = open(argv[2],O_RDWR|O_TRUNC);
    else 
        destfd = open(argv[2],O_CREAT|O_WRONLY|O_TRUNC,0664);

    if(destfd < 0)
        sys_err("open destfd");

    ftruncate(destfd,size);

    int count = size / LEN;
    if(size % LEN == 0)
    {
        int i;
        for(i = 0;i < count; i++) 
        {
            mm = mmap(NULL,LEN,PROT_READ|PROT_WRITE,MAP_PRIVATE,srcfd,LEN*i);
            lseek(destfd,i*LEN,SEEK_SET);
            write(destfd,mm,LEN);
            munmap(mm,LEN);
        }
    }
    else
    {
        int last_len = size % LEN;
        int i;

        for(i = 0;i < count; i++) 
        {
            mm = mmap(NULL,LEN,PROT_READ|PROT_WRITE,MAP_PRIVATE,srcfd,LEN*i);
            lseek(destfd,i*LEN,SEEK_SET);
            write(destfd,mm,LEN);
            munmap(mm,LEN);
        }
        mm = mmap(NULL,last_len,PROT_READ|PROT_WRITE,MAP_PRIVATE,srcfd,LEN*count);
        lseek(destfd,count*LEN,SEEK_SET);
        write(destfd,mm,last_len);
        munmap(mm,last_len);
        
    }
    close(srcfd);
    close(destfd);

    return 0;
}
