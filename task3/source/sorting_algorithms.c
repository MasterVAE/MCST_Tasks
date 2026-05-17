#include <string.h>
#include <ctype.h>

#include "sorting_algorithms.h"
#include "sorter.h"

// Посимвольное сравнение строк
int plain(const void* line1_void, const void* line2_void)
{
    const Line* line1 = (const Line*)line1_void;
    const Line* line2 = (const Line*)line2_void;

    return strcmp(line1->string, line2->string);
}

// Лексикографическое сравнение строк
int lex(const void* line1_void, const void* line2_void)
{
    const Line* line1 = (const Line*)line1_void;
    const Line* line2 = (const Line*)line2_void;

    size_t len = line1->len > line2->len ? line2->len : line1->len;

    const char* str1 = line1->string;
    const char* str2 = line2->string;

    for(size_t i = 0; i < len; i++)
    {
        int dif = tolower(str1[i]) - tolower(str2[i]);
        if(dif > 0) return 1;
        else if(dif < 0) return -1;
    }

    if(line1->len == line2->len) return 0;

    return line1->len > line2->len ? 1 : -1;
}


// Обратное посимвольное сравнение строк
int rplain(const void* line1_void, const void* line2_void)
{
    const Line* line1 = (const Line*)line1_void;
    const Line* line2 = (const Line*)line2_void;

    size_t len = line1->len > line2->len ? line2->len : line1->len;

    const char* str1 = line1->string;
    const char* str2 = line2->string;

    for(size_t i = 0; i < len; i++)
    {
        int dif = str1[line1->len - i - 1] - str2[line2->len - i - 1];
        if(dif > 0) return 1;
        else if(dif < 0) return -1;
    }

    if(line1->len == line2->len) return 0;

    return line1->len > line2->len ? 1 : -1;
}

// Обратное лексикографическое сравнение строк
int rlex(const void* line1_void, const void* line2_void)
{
    const Line* line1 = (const Line*)line1_void;
    const Line* line2 = (const Line*)line2_void;

    size_t len = line1->len > line2->len ? line2->len : line1->len;

    const char* str1 = line1->string;
    const char* str2 = line2->string;

    for(size_t i = 0; i < len; i++)
    {
        int dif = tolower(str1[line1->len - i - 1]) - tolower(str2[line2->len - i - 1]);
        if(dif > 0) return 1;
        else if(dif < 0) return -1;
    }

    if(line1->len == line2->len) return 0;

    return line1->len > line2->len ? 1 : -1;
}