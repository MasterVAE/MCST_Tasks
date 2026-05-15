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
        return 1;
    }

    Tokenizator* tokenizator = Tokenize(buffer);
    if(!tokenizator)
    {
        free(buffer);
        DestroyTokenizator(tokenizator);
        return 2;
    }

    free(buffer);

    Tree* tree = Parse(tokenizator);
    if(!tree) return 3;

    SetupTree(tokenizator);

    Run(tree);

    DestroyTokenizator(tokenizator);
    return 0;
}