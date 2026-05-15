#ifndef TOKENIZATOR_H
#define TOKENIZATOR_H

#include <stdlib.h>

#include "tree.h"

struct Tokenizator
{
    TreeNode* tokens;
    size_t tokens_count;
};

Tokenizator* CreateTokenizator();
void DestroyTokenizator(Tokenizator* tokenizator);
Tokenizator* Tokenize(const char* string);

#endif // TOKENIZATOR_H