#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

static int Sort(size_t threads_count, size_t array_len, int* array);
void* ChunkSort(void *arg);
int Compare(const void *a, const void *b);

typedef struct 
{
    int *array;
    size_t start;
    size_t end;
} ThreadData;

void* ChunkSort(void *arg) 
{
    ThreadData *data = (ThreadData*)arg;
    qsort(data->array + data->start, data->end - data->start, sizeof(int), Compare);

    return NULL;
}

int Compare(const void *a, const void *b) 
{
    int a_cast = *(const int*)a;
    int b_cast = *(const int*)b;

    return (a_cast - b_cast);
}

int main(int argc, char* argv[])
{
    if(argc != 2) return 1;
    size_t threads_count = 0;
    sscanf(argv[1], "%lu", &threads_count);

    char *line = NULL;
    size_t size = 0;
    size_t len = getline(&line, &size, stdin);

    if (len > 0 && (line[len - 1] == '\n' || line[len - 1] == EOF)) line[len - 1] = '\0';

    size_t capacity = 1;
    int* array = (int*)calloc(capacity, sizeof(int));
    size_t count = 0;

    char *ptr = line;
    while (*ptr) 
    {
        while (isspace((unsigned char)*ptr)) ptr++;
        if (*ptr == '\0') break;

        char *end;
        int element = (int)strtol(ptr, &end, 10);
        if (ptr == end) break;

        if (count >= capacity) 
        {
            capacity *= 2;
            array = (int*)realloc(array, capacity * sizeof(int));
        }
        array[count++] = element;
        ptr = end;
    }
    if (count == 0) 
    {
        free(array);
        return 0; 
    }

    int sort = Sort(threads_count, count, array);
    if(sort != 0) return sort;

    return 0;
}

static int Sort(size_t threads_count, size_t array_len, int* array)
{
    assert(array);

    pthread_t* threads = (pthread_t*)calloc(threads_count, sizeof(pthread_t));
    if(!threads) return 2;

    ThreadData* threads_data = (ThreadData*)calloc(threads_count, sizeof(ThreadData));
    if(!threads_data) return 2;

    size_t base = array_len / threads_count;
    size_t rem  = array_len % threads_count;
    for (size_t i = 0; i < threads_count; i++) 
    {
        threads_data[i].array = array;
        threads_data[i].start = i * base + (i < rem ? i : rem);
        threads_data[i].end   = threads_data[i].start + base + (i < rem ? 1 : 0);

        pthread_create(&threads[i], NULL, ChunkSort, &threads_data[i]);
    }

    for (size_t i = 0; i < threads_count; i++) pthread_join(threads[i], NULL);

    bool found = true;
    while(found)
    {
        found = false;

        int min_found = 0;
        size_t thread_found = 0;

        for(size_t i = 0; i < threads_count; i++)
        {
            if(threads_data[i].start < threads_data[i].end)
            {
                if(!found || array[threads_data[i].start] < min_found)
                {
                    found = true;
                    min_found = array[threads_data[i].start];
                    thread_found = i;
                }
            }
        }

        if(found)
        {
            printf("%d ", min_found);
            threads_data[thread_found].start++;
        }
    }

    printf("\n");

    return 0;
}