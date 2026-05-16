#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static const char* const filename = "/nonexisting_file";

int main(void)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) 
    {

        perror("Can't open file");

        printf("sys_errlist: %s\n", strerror(errno));

        switch (errno) 
        {
            case ENOENT:
                printf("Errno = ENOENT\n");
                break;
            default:
                printf("Errno = %d\n", errno);
                break;
        }

        exit(errno);
    }

    close(fd);
    return 0;
}