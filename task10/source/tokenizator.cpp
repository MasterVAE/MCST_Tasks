#include <assert.h>
#include <string.h>

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

    free(tokenizator->tokens);
    free(tokenizator);
}

Tokenizator* Tokenize(const char* string)
{
    Tokenizator* tokenizator = CreateTokenizator();
    if(!tokenizator) return NULL;

    size_t offset = 0;

    while(*string != '\0')
    {
        if(*string == ' ')
        {
            string++;
        }
        else if(!strncmp(string, "(",  1))
        {
            AddToken(tokenizator, NODE_OPERATION, NodeValue {.operation = OP_BRACKET_OPEN});
            string += 1;
        }
        else if(!strncmp(string, ")",  1))
        {
            AddToken(tokenizator, NODE_OPERATION, NodeValue {.operation = OP_BRACKET_CLOSE});
            string += 1;
        }
        else if(!strncmp(string, "AND",  3))
        {
            AddToken(tokenizator, NODE_OPERATION, NodeValue {.operation = OP_AND});
            string += 3;
        }
        else if(!strncmp(string, "OR",  2))
        {
            AddToken(tokenizator, NODE_OPERATION, NodeValue {.operation = OP_OR});
            string += 2;
        }
        else if(!strncmp(string, "NOT",  3))
        {
            AddToken(tokenizator, NODE_OPERATION, NodeValue {.operation = OP_NOT});
            string += 3;
        }
        else if(*string <= 'Z' && *string >= 'A')
        {
            AddToken(tokenizator, NODE_VARIABLE, NodeValue {.variable = *string});
            string += 1;
        }
        else
        {
            return NULL;
        }
    }
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
