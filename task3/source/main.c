#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "sorter.h"
#include "sorting_algorithms.h"

static char* ReadFileToBuffer(const char* filename);
static size_t FileLen(FILE* file);

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        fprintf(stderr, "ERROR: Must have 3 params\n");
        return 1;
    }

    const char* in_filename = argv[1];
    const char* out_filename = argv[2];

    char* buffer = ReadFileToBuffer(in_filename);

    Sorter* sorter = CreateSorter();
    LoadSorter(sorter, buffer);

    if      (!strcmp(argv[3], "plain"))     SortSorter(sorter, plain);
    else if (!strcmp(argv[3], "lex"))       SortSorter(sorter, lex);
    else if (!strcmp(argv[3], "rplain"))    SortSorter(sorter, rplain);
    else if (!strcmp(argv[3], "rlex"))      SortSorter(sorter, rlex);
    else 
    {
        fprintf(stderr, "ERROR: Unknown soring algorithm\n");
        return 1;
    }


    FILE* out_file = fopen(out_filename, "w+");
    if(!out_file)
    {
        fprintf(stderr, "ERROR: Cannot open file %s\n", out_filename);
        return 1;

    }
    for(size_t i = 0; i < sorter->lines_count; i++)
    {
        fprintf(out_file, "%s\n", sorter->lines[i].string);
    }
    fclose(out_file);

    DestroySorter(sorter);
    free(buffer);
}

// Помещает содержимое файла в аллоцируемый буффер
static char* ReadFileToBuffer(const char* filename)
{
    assert(filename);

    FILE* file = fopen(filename, "r+");
    if(!file)
    {
        fprintf(stderr, "ERROR: Cannot open file\n");
        return NULL;
    }

    size_t len = FileLen(file);

    char* buffer = (char*)calloc(len + 1, sizeof(char));
    if(!buffer)
    {
        fprintf(stderr, "ERROR: Cannot allocate memory\n");
        fclose(file);
        return NULL;
    }
    fread(buffer, len, 1, file);
    fclose(file);
    return buffer;
}

// Размер файла
static size_t FileLen(FILE* file)
{
    assert(file);

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);

    return (size_t)len;
}