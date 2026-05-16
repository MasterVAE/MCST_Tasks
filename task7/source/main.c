#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

static const char* const parent_filename = "parent_copy";
static const char* const child_filename = "child_copy";

static size_t FileLen(FILE* file);

int main(int argc, char* argv[])
{
    if(argc != 2) return 1;

    FILE* file = fopen(argv[1], "rb+");
    size_t len = FileLen(file);

    pid_t pid = fork();
    if (pid < 0) return 2;

    if (pid == 0) 
    {
        FILE* child_file = fopen(child_filename, "wb+");
        char* buffer = (char*)calloc(len + 1, sizeof(char));
        fread(buffer, len, 1, file);
        fwrite(buffer, len, 1, child_file);

        printf("Child:\n");
        printf("%s\n", buffer);

        fclose(child_file);
    }
    else
    {
        FILE* parent_file = fopen(parent_filename, "wb+");
        char* buffer = (char*)calloc(len + 1, sizeof(char));
        fread(buffer, len, 1, file);
        fwrite(buffer, len, 1, parent_file);

        printf("Parent:\n");
        printf("%s\n", buffer);

        fclose(parent_file);
    }

    fclose(file);

    return 0;
}

static size_t FileLen(FILE* file)
{
    assert(file);

    fseek(file, 0, SEEK_END);
    ssize_t len = ftell(file);
    fseek(file, 0, SEEK_SET);

    return (size_t)len;
}