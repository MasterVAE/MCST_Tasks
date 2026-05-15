#include <stdio.h>

#include "tree.h"
#include "runner.h"
#include "tokenizator.h"

int main()
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t count;

    count = getline(&buffer, &buffer_size, stdin);

    if(count == -1) return 1;

    Tokenizator* tokenizator = Tokenize(buffer);
    printf("buffer %s\n", buffer);
    if(!tokenizator) return 2;
    return 0;
}