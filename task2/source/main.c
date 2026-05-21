#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv)
{
    if (argc != 3) 
    {
        fprintf(stderr, "ERROR: Must be for 2 arguments\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "ERROR: Creating process error\n");
        return 2;
    }

    if (pid == 0) // дочерний процесс, отправляющий сообщения
    {
        int fd_out = open(argv[1], O_WRONLY);
        if (fd_out < 0)
        {
            fprintf(stderr, "ERROR: Cannot open file %s\n", argv[1]);
            return 3;
        }

        char buffer[BUFFER_SIZE];
        ssize_t n = 0;
        while ((n = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) 
        {
            if (write(fd_out, buffer, (size_t)n) < 0) break;
        }

        close(fd_out);
    }
    else // родительский процесс, получающий сообщения
    {
        int fd_in = open(argv[2], O_RDONLY);
        if (fd_in < 0) 
        {   
            fprintf(stderr, "ERROR: Cannot open file %s\n", argv[2]);
            return 4;
        }
        
        char buffer[BUFFER_SIZE] = {0};
        ssize_t n = 0;
        while ((n = read(fd_in, buffer, sizeof(buffer))) > 0) 
        {
            if (write(STDOUT_FILENO, buffer, (size_t)n) < 0) break;
        }

        close(fd_in);
    }

    return 0;
}