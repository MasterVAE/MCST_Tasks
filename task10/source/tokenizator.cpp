#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "tokenizator.h"

static void AddToken(Tokenizator* tokenizator, NodeType type, NodeValue value);

Tokenizator* CreateTokenizator()
{
    Tokenizator* tokenizator = (Tokenizator*)calloc(1, sizeof(Tokenizator));
    if(!tokenizator) return NULL;

    tokenizator->tokens = (TreeNode*)calloc(1, sizeof(TreeNode));
    if(!tokenizator->tokens)
    {
        free(tokenizator);
        return NULL;
    }
    tokenizator->tokens_count = 0;

    return tokenizator;
}

void DestroyTokenizator(Tokenizator* tokenizator)
{
    if(!tokenizator) return;

    DestroyTree(tokenizator->tree);

    free(tokenizator->tokens);
    free(tokenizator);
}

Tokenizator* Tokenize(const char* string)
{
    Tokenizator* tokenizator = CreateTokenizator();
    if(!tokenizator) return NULL;

    bool start = true;
    while(*string != '\n')
    {
        if(*string == ' ')
        {
            string++;
            start = true;
        }
        else if(!strncmp(string, "(",  1))
        {
            AddToken(tokenizator, NODE_OPERATION, NodeValue {.operation = OP_BRACKET_OPEN});
            start = true;
            string += 1;
        }
        else if(!strncmp(string, ")",  1))
        {
            AddToken(tokenizator, NODE_OPERATION, NodeValue {.operation = OP_BRACKET_CLOSE});
            start = true;
            string += 1;
        }
        else if(!strncmp(string, "AND",  3))
        {
            AddToken(tokenizator, NODE_OPERATION, NodeValue {.operation = OP_AND});
            start = true;
            string += 3;
        }
        else if(!strncmp(string, "OR",  2))
        {
            AddToken(tokenizator, NODE_OPERATION, NodeValue {.operation = OP_OR});
            start = true;
            string += 2;
        }
        else if(!strncmp(string, "NOT",  3))
        {
            AddToken(tokenizator, NODE_OPERATION, NodeValue {.operation = OP_NOT});
            start = true;
            string += 3;
        }
        else if(*string <= 'Z' && *string >= 'A')
        {
            if(!start) return NULL;
            
            AddToken(tokenizator, NODE_VARIABLE, NodeValue {.variable = *string});
            string += 1;
            start = false;
        }
        else
        {
            return NULL;
        }
    }

    return tokenizator;
}

static void AddToken(Tokenizator* tokenizator, NodeType type, NodeValue value)
{
    assert(tokenizator);

    tokenizator->tokens_count++;
    tokenizator->tokens = (TreeNode*)realloc(tokenizator->tokens, 
                                             sizeof(TreeNode) * tokenizator->tokens_count);
    TreeNode* node = tokenizator->tokens + tokenizator->tokens_count - 1;
    node->type = type;
    node->value = value;
}
