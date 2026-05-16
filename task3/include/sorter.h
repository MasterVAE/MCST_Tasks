#ifndef SORTER_H
#define SORTER_H

#include <stdlib.h>

typedef struct 
{
    const char* string;
    size_t len;
} Line;


typedef struct 
{
    size_t capacity;
    size_t lines_count;
    Line* lines;
} Sorter;

Sorter* CreateSorter();
void DestroySorter(Sorter* sorter);

void LoadSorter(Sorter* sorter, char* buffer);
void SortSorter(Sorter* sorter, int (*sort_func_ptr)(const void*, const void*));

#endif // SORTER_H