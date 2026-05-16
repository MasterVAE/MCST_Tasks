#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main()
{
    char line[1024];
    if (!fgets(line, sizeof(line), stdin))return 0;

    size_t len = strlen(line);
    if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == EOF)) line[len - 1] = '\0';

    size_t capacity = 1;
    int* array = (int*)calloc(capacity, sizeof(int));
    size_t elements_count = 0;

    char *ptr = line;
    while (*ptr) 
    {
        while (isspace((unsigned char)*ptr)) ptr++;
        if (*ptr == '\0') break;

        char *end;
        int element = (int)strtol(ptr, &end, 10);
        if (ptr == end) break;

        if (elements_count >= capacity) 
        {
            capacity *= 2;
            array = (int*)realloc(array, capacity * sizeof(int));
        }
        array[elements_count++] = element;
        ptr = end;
    }
    if (elements_count == 0) { free(array); return 0; }

    size_t max_len = 1;
    int max_sum = array[0];
    size_t best_start = 0;
    size_t current_start = 0;
    size_t current_len = 1;
    int current_sum = array[0];


    size_t i = 1;
    while(i < elements_count)
    {
        while(i < elements_count && array[i] > array[i - 1])
        {   
            current_sum += array[i];
            current_len++;
            i++;
        }

        if(current_len > max_len)
        {
            max_len = current_len;
            max_sum = current_sum;
            best_start = current_start;
        }
        else if(current_len == max_len)
        {
            if(current_sum > max_sum)
            {
                max_sum = current_sum;
                best_start = current_start;
            }
        }

        current_len = 1;
        current_start = i;
        current_sum = array[current_start];

        i++;
    }


    for(size_t j = 0; j < max_len; j++)
    {
        printf("%d ", array[best_start + j]);
    }
    printf("\n");

    return 0;
}