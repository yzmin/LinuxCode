#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define N 5

struct child_task {
    char src[256];
    char dest[256];
    int addr;
    int size;
    int num;
};

void sys_err(const char *str)
{
    perror(str);
    exit(-1);
}
int main(int argc, char *argv[])
{
    int nfork, i, task_addr, task_size, total_size, fddest, tmpfd;
    pid_t pid;
    struct stat sbuf;
    int *mem;

    if (argc < 3) {
        printf("./mycp src dest\n");
        exit(-1);
    }
    if (argc == 3)
        nfork = N;
    else 
        nfork = atoi(argv[3]);

    if (stat(argv[1], &sbuf) < 0)
        sys_err("stat");
    total_size = sbuf.st_size;
    fddest = open(argv[2], O_CREAT|O_RDWR, 0644);
    if (fddest < 0)
        sys_err("open");
    if (lseek(fddest, total_size-1, SEEK_SET) < 0)
        sys_err("lseek");
    write(fddest, "\0", 1);
    close(fddest);

    //struct child_task work[nfork];
    struct child_task *work = malloc(nfork * sizeof(struct child_task));
    task_size = total_size / nfork;
    for (i = 0; i < nfork-1; i++) {
        strcpy(work[i].src ,argv[1]);
        strcpy(work[i].dest ,argv[2]);
        work[i].addr = i * task_size;
        work[i].size = task_size;
        work[i].num = i;
    }
    /* 最后一个进程拷贝字节 */
    strcpy(work[i].src ,argv[1]);
    strcpy(work[i].dest ,argv[2]);
    work[i].addr = i * task_size;
    work[i].size = total_size - work[i].addr;
    work[i].num = i;

    tmpfd = open("tmpfile", O_CREAT|O_RDWR|O_EXCL, 0664);
    if (tmpfd < 0)
        sys_err("open tmpfile");

    ftruncate(tmpfd, nfork*sizeof(int));

    mem = mmap(NULL, nfork*sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, tmpfd, 0);
    if (mem == MAP_FAILED)
        sys_err("mmap");
    memset(mem, 0, nfork*sizeof(int));
    //int mem[5];  mem[0]=20   mem[1] = 50 ...

    unlink("tmpfile");   //删除临时文件

    for (i = 0; i < nfork; i++) {
        if ((pid = fork()) < 0)
            sys_err("fork");
        else if (pid == 0) {
            /*in child*/
            int fdsrc, fddest, j, len;
            char buf[4096];
            fdsrc = open(work[i].src, O_RDONLY);
            if (fdsrc < 0)
                sys_err("open src");
            fddest = open(work[i].dest, O_WRONLY);
            if (fddest < 0)
                sys_err("open dest");
            if (lseek(fdsrc, work[i].addr, SEEK_SET) < 0)
                sys_err("lseek fdsrc");
            if (lseek(fddest, work[i].addr, SEEK_SET) < 0)
                sys_err("lseek fddest");

            for (j = 0; j < work[i].size; j++) {
                len = read(fdsrc, buf, 1);
                if (len < 0)
                    sys_err("read");
                write(fddest, buf, len);
                mem[work[i].num]++;
                //                usleep(100000);
            }
            close(fdsrc);
            close(fddest);
            break;
        }
        if(pid > 0)
        {
            printf("parent %d\n",i);
        }
    }

    if (pid > 0) {
        pid = fork();
        /* 打印拷贝进程 */
        if (pid == 0) {
            int i, sum = 0;
            while (sum < total_size) {
                sum = 0;
                for (i = 0; i < nfork; i++) {
                    sum += mem[i];
                }
                printf("%d / %d\n", sum, total_size);
                usleep(100000);
            }
        }
        else if (pid > 0) {
            for (i = 0; i < nfork+1; i++)
                wait(NULL);
        }
        else {
            sys_err("fork");
        }
    }

    free(work);
    return 0;
}
