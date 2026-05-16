#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <time.h>

const char* FileType(mode_t mode);
void SetPermissions(mode_t mode, char *str);

int main(int argc, char* argv[])
{
    if(argc != 2) return 1;

    struct stat* stats = (struct stat*)calloc(1, sizeof(struct stat));
    stat(argv[1], stats);

    printf("File: %s\n", argv[1]);
    printf("Size: %ld\t  Blocks: %ld\n", stats->st_size, stats->st_blocks);
    printf("%s\n", FileType(stats->st_mode));

    printf("Device: %u,%u\t  Links: %lu\n", major(stats->st_dev), minor(stats->st_dev), 
                                            stats->st_nlink);

    char str[10] = {0};
    SetPermissions(stats->st_mode, str);
    printf("Permissions: %s\n", str);

    char time_buf[64];
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&stats->st_atim.tv_sec));
    printf("Access: %s\n", time_buf);

    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&stats->st_mtim.tv_sec));
    printf("Modify: %s\n", time_buf);

    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&stats->st_ctim.tv_sec));
    printf("Change: %s\n", time_buf);

    printf(" IO Block: %ld\n", stats->st_blksize);

    return 0;
}


const char* FileType(mode_t mode)
{
    if(S_ISREG(mode))  return "regular file";
    if(S_ISDIR(mode))  return "directory";
    if(S_ISLNK(mode))  return "symbolic link";
    if(S_ISCHR(mode))  return "character device";
    if(S_ISBLK(mode))  return "block device";
    if(S_ISFIFO(mode)) return "FIFO file";
    if(S_ISSOCK(mode)) return "socket";

    return "unknown type";
}

void SetPermissions(mode_t mode, char *str) 
{
    str[0] = (mode & S_IRUSR) ? 'r' : '-';
    str[1] = (mode & S_IWUSR) ? 'w' : '-';
    str[2] = (mode & S_IXUSR) ? 'x' : '-';
    str[3] = (mode & S_IRGRP) ? 'r' : '-';
    str[4] = (mode & S_IWGRP) ? 'w' : '-';
    str[5] = (mode & S_IXGRP) ? 'x' : '-';
    str[6] = (mode & S_IROTH) ? 'r' : '-';
    str[7] = (mode & S_IWOTH) ? 'w' : '-';
    str[8] = (mode & S_IXOTH) ? 'x' : '-';
    str[9] = '\0';
}