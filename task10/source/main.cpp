#include <stdio.h>

#include "tree.h"
#include "runner.h"
#include "parser.h"
#include "tokenizator.h"

int main()
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t count;

    count = getline(&buffer, &buffer_size, stdin);

    if(count == -1)
    {
        free(buffer);
        fprintf(stderr, "ERROR: Failed to getline\n");
        return 1;
    }

    Tokenizator* tokenizator = Tokenize(buffer);
    if(!tokenizator)
    {
        free(buffer);
        fprintf(stderr, "ERROR: Tokenization failed\n");
        return 2;
    }

    free(buffer);

    Tree* tree = Parse(tokenizator);
    if(!tree)
    {
        fprintf(stderr, "ERROR: Parsing error\n");
        return 3;
    }

    SetupTree(tokenizator);

    Run(tree);

    DestroyTokenizator(tokenizator);
    return 0;
}