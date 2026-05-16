#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "sorter.h"

const size_t default_capaciry = 8;

Sorter* CreateSorter()
{
    Sorter* sorter = (Sorter*)calloc(1, sizeof(Sorter));
    sorter->capacity = default_capaciry;
    sorter->lines = (Line*)calloc(sorter->capacity, sizeof(Line));
    if(!sorter->lines)
    {
        free(sorter);
        return NULL;
    }

    sorter->lines_count = 0;

    return sorter;
}

void DestroySorter(Sorter* sorter)
{
    if(!sorter) return;

    free(sorter->lines);
    free(sorter);
}

void LoadSorter(Sorter* sorter, char* buffer)
{
    assert(sorter);
    assert(buffer);

    bool start = true;
    char* current_start = buffer;
    size_t current_len = 0;
    char c = 0;
    while((c = *buffer) != '\0')
    {
        if(c == '\n')
        {
            if(!start)
            {
                sorter->lines_count++;
                if(sorter->lines_count > sorter->capacity)
                {
                    sorter->capacity *= 2;
                    sorter->lines = (Line*)realloc(sorter->lines, sorter->capacity * sizeof(Line));
                    if(!sorter->lines)
                    {
                        fprintf(stderr, "ERROR: Cannot allocate memory\n");
                        return;
                    }
                }

                sorter->lines[sorter->lines_count - 1].string = current_start;
                sorter->lines[sorter->lines_count - 1].len = current_len;
            }

            start = true;
            current_start = buffer + 1;
            current_len = 0;

            *buffer = '\0';
        }
        else if(c != ' ')
        {
            start = false;
        }
        current_len++;
        buffer++;
    }
}
void SortSorter(Sorter* sorter, int (*sort_func_ptr)(const void*, const void*))
{
    assert(sorter);
    assert(sort_func_ptr);

    qsort(sorter->lines, sorter->lines_count, sizeof(Line), sort_func_ptr);
}