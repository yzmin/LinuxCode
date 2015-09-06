#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void do_ls(char[]);
void do_stat(char*);
void show_file_info(char*, struct stat*);
void mode_str(int, char[]);
char *uid_str(uid_t);
char *gid_str(gid_t);

int main(int argc, char *argv[])
{
    if(argc == 1)
        do_ls(".");
    else
        while(--argc){
            printf("%s:\n", *++argv);
            do_ls(*argv);
        } 

    return 0;
}

void do_ls(char dirname[])
{
    DIR *dir_ptr;           /* the directory */
    struct dirent *direntp; /* each entry */
    char full_path[256];

    if((dir_ptr = opendir(dirname)) == NULL){
        fprintf(stderr, "ls2: cannot open %s\n", dirname);
    }else{
        while((direntp = readdir(dir_ptr)) != NULL){
            strcpy(full_path, dirname);
            int dir_len = strlen(dirname);
            if(dirname[dir_len - 1] != '/'){  /* 处理目录字符串最后没有‘/’的情况 */
                full_path[dir_len] = '/';
                strcpy(full_path + dir_len + 1, direntp->d_name);
            }else
                strcpy(full_path + dir_len, direntp->d_name);

            do_stat(full_path);
        } 
        closedir(dir_ptr);
    } 
} 
void do_stat(char *filename) /* 获得目录中文件的相关信息 */
{
    struct stat info;

    /* 如果filename最后没有‘/’的话，stat调用失败 */
    if(stat(filename, &info) == -1){ /* cannot stat */
        perror("stat"); /* say why */
        printf("filename:%s\n", filename);
    }else{
        char *pname = strrchr(filename, '/');
        show_file_info(pname + 1, &info);
    }
}

void show_file_info(char *filename, struct stat *info_p) /* 打印文件的相关信息 */
{
    char modestr[11];

    mode_str(info_p->st_mode, modestr);

    printf("%s", modestr);
    printf("%3d ", (int)info_p->st_nlink);
    printf("%-8s", uid_str(info_p->st_uid));
    printf("\t%-8s", gid_str(info_p->st_gid));
    printf("\t%4ld ", (long)info_p->st_size);
    printf("%.12s ", 4 + ctime(&info_p->st_mtime));
    printf("%s\n", filename);
}

void mode_str(int mode, char str[]) /* 将文件的相关信息转化成 “crw-rw---"的形式 */
{
    strcpy(str, "----------"); /* default = no perms */
    if(S_ISDIR(mode)) str[0] = 'd'; /* directory */
    if(S_ISCHR(mode)) str[0] = 'c'; /* char device */
    if(S_ISBLK(mode)) str[0] = 'b'; /* block device */
    if(S_ISLNK(mode)) str[0] = 'l';

    if(mode & S_IRUSR) str[1] = 'r'; /* 3 bits for user */
    if(mode & S_IWUSR) str[2] = 'w';
    if(mode & S_IXUSR) str[3] = 'x';

    if(mode & S_IRGRP) str[4] = 'r'; /* 3 bits for group */
    if(mode & S_IWGRP) str[5] = 'w';
    if(mode & S_IXGRP) str[6] = 'x';

    if(mode & S_IROTH) str[7] = 'r'; /* 3 bits for other */
    if(mode & S_IWOTH) str[8] = 'w';
    if(mode & S_IXOTH) str[9] = 'x';
}

char *uid_str(uid_t uid) /* 将uid转化成username */
{
    static char numstr[10];
    struct passwd *pw_ptr;

    if((pw_ptr = getpwuid(uid)) == NULL){
        sprintf(numstr, "%d", uid);
        return numstr;
    }else
        return pw_ptr->pw_name;
}

char *gid_str(gid_t gid) /* 将gid转化成groupname */
{
    static char numstr[10];
    struct group *grp_ptr;

    if((grp_ptr = getgrgid(gid)) == NULL){
        sprintf(numstr, "% d", gid);
        return numstr;
    }else
        return grp_ptr->gr_name;
}
