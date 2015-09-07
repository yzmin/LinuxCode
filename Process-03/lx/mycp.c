#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

struct infostruct
{
    int lenSize;
    int pstart;
};

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}

int fileSize(const char *filename)
{
    struct stat buf;
    if(stat(filename,&buf) != 0)
    {
        perror("stat");
        return -1;
    }

    return buf.st_size;
}

void copyBytes()
{

}

int main(int argc,char *argv[])
{
    int proNum;
    int fsize;
    int srcfd;
    int destfd;
    char buf[1024];
    int len;

    if(argc < 3)
    {
        fprintf(stderr,"./a.out src dest\n");
        exit(-1);
    }
    else if(argc == 3)
    {
        srcfd = open(argv[1],O_RDONLY);
        destfd = open(argv[2],O_CREAT|O_TRUNC|O_WRONLY,0664);

        while((len = read(srcfd,buf,sizeof(buf))) > 0)
        {
            write(destfd,buf,len);
        }

    }
    else if(argc == 4)
    {
        pid_t pid;
        proNum = atoi(argv[3]);
        fsize = fileSize(argv[1]);

        srcfd = open(argv[1],O_RDONLY);
        destfd = open(argv[2],O_CREAT|O_TRUNC|O_WRONLY,0664);
        ftruncate(destfd,fsize);

        pid = fork();
        if(pid > 0)
        {
            lseek(srcfd,0,SEEK_SET);
            lseek(destfd,0,SEEK_SET);
            while((len = read(srcfd,buf,sizeof(buf))) > 0)
            {
                write(destfd,buf,len);
                if(lseek(srcfd,0,SEEK_CUR) > fsize/2)
                    break;
            }
            wait(NULL);
            close(srcfd);
            close(destfd);
            exit(0);
        }
        else if(pid == 0)
        {
            close(srcfd);
            close(destfd);
            srcfd = open(argv[1],O_RDONLY);
            destfd = open(argv[2],O_CREAT|O_TRUNC|O_WRONLY,0664);

            lseek(srcfd,fsize/2,SEEK_SET);
            lseek(destfd,fsize/2,SEEK_SET);
            while((len = read(srcfd,buf,sizeof(buf))) > 0)
            {
                write(destfd,buf,len);
            }
            close(srcfd);
            close(destfd);
            exit(0);
        }
        else 
        {
            sys_err("fork");
        }
    }
    return 0;
}
