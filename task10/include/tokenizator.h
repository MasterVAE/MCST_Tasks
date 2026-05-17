#ifndef TOKENIZATOR_H
#define TOKENIZATOR_H

#include <stdlib.h>

#include "tree.h"

// Стуктура, хранящая данные токенизатора
struct Tokenizator
{
    TreeNode* tokens;
    size_t tokens_count;

    Tree* tree;
};

Tokenizator* CreateTokenizator();
void DestroyTokenizator(Tokenizator* tokenizator);
Tokenizator* Tokenize(const char* string);

#endif // TOKENIZATOR_H