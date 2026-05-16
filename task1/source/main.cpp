#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

static int Sort(size_t threads_count, size_t array_len, int* array);
void* ChunkSort(void *arg);
int Compare(const void *a, const void *b) ;

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
    int a_cast = *(int*)a;
    int b_cast = *(int*)b;

    return (a_cast - b_cast);
}

int main(int argc, char* argv[])
{
    if(argc != 2) return 1;
    size_t threads_count = 0;
    sscanf(argv[1], "%lu", &threads_count);

    int capacity = 64;
    int* array = (int*)calloc(capacity, sizeof(int));
    if (!array) return 2;

    int count = 0;
    int value = 0;
    while (scanf("%d", &value) == 1) 
    {
        if (count >= capacity)
        {
            capacity *= 2;
            array = (int*)realloc(array, capacity * sizeof(int));
            if(!array) return 2;
        }
        array[count++] = value;
    }

    if (count == 0) 
    {
        free(array);
        return 0; 
    }

    int sort = Sort(threads_count, count, array);
    if(sort != 0) return sort;

    for(size_t i = 0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

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

    return 0;
}