#include <assert.h>
#include <stdio.h>

#include "parser.h"
#include "tree.h"
#include "tokenizator.h"

static TreeNode* Or(Tokenizator* tokenizator);
static TreeNode* And(Tokenizator* tokenizator);
static TreeNode* Not(Tokenizator* tokenizator);

static TreeNode* Brackets(Tokenizator* tokenizator);
static TreeNode* Var(Tokenizator* tokenizator);

static size_t current_token;

static bool CheckOperation(Tokenizator* tokenizator, Operation op);

//#define LOG(string) printf(string);
#define LOG(string)

// Парсинг токенов в дерево
Tree* Parse(Tokenizator* tokenizator)
{
    assert(tokenizator);

    tokenizator->tree = CreateTree();
    if(!tokenizator->tree) return NULL;

    tokenizator->tree->root = Or(tokenizator);

    if(!tokenizator->tree->root) return NULL;

    return tokenizator->tree;
}

// Парсинг конструкции OR
static TreeNode* Or(Tokenizator* tokenizator)
{
    assert(tokenizator);

    TreeNode* node = And(tokenizator);
    if(!node) return NULL;

    while(CheckOperation(tokenizator, OP_OR) && !CheckOperation(tokenizator, OP_BRACKET_CLOSE))
    {
        current_token++;

        TreeNode* node1 = And(tokenizator);
        if(!node1)
        {
            fprintf(stderr, "ERROR: Fail in Or parsing\n");
            return NULL;
        }

        TreeNode* node2 = CreateNode(NODE_OPERATION, {.operation = OP_OR});
        node2->left = node;
        node2->right = node1;
        node = node2;
    }

    return node;
}

// Парсинг конструкции AND
static TreeNode* And(Tokenizator* tokenizator)
{
    assert(tokenizator);

    TreeNode* node = Not(tokenizator);
    if(!node) return NULL;

    while(CheckOperation(tokenizator, OP_AND) && !CheckOperation(tokenizator, OP_BRACKET_CLOSE))
    {
        current_token++;

        TreeNode* node1 = Not(tokenizator);
        if(!node1)
        {
            fprintf(stderr, "ERROR: Fail in And parsing\n");
            return NULL;
        }

        TreeNode* node2 = CreateNode(NODE_OPERATION, {.operation = OP_AND});
        node2->left = node;
        node2->right = node1;
        node = node2;
    }

    return node;
}

// Парсинг конструкции NOT
static TreeNode* Not(Tokenizator* tokenizator)
{
    assert(tokenizator);

    if(CheckOperation(tokenizator, OP_NOT))
    {
        current_token++;
        TreeNode* node = Not(tokenizator);

        TreeNode* new_node = CreateNode(NODE_OPERATION, {.operation = OP_NOT});
        new_node->left = node;

        return new_node;
    }
    else
    {
        return Brackets(tokenizator);
    }
}

// Парсинг скобок
static TreeNode* Brackets(Tokenizator* tokenizator)
{
    assert(tokenizator);

    if(CheckOperation(tokenizator, OP_BRACKET_OPEN))
    {
        current_token++;
        TreeNode* node = Or(tokenizator);
        if(!node) return NULL;


        if(CheckOperation(tokenizator, OP_BRACKET_CLOSE)) 
        {
            current_token++;
            return node;
        }
        else
        {
            fprintf(stderr, "ERROR: Fail in Brackets parsing\n");
            return NULL;
        }
    }
    else
    {
        return Var(tokenizator);
    }
}

// Парсинг переменных
static TreeNode* Var(Tokenizator* tokenizator)
{
    assert(tokenizator);

    if(tokenizator->tokens_count > current_token 
    && tokenizator->tokens[current_token].type == NODE_VARIABLE) 
    {
        if(!tokenizator->tree->variables[tokenizator->tokens[current_token].value.variable - 'A'])
        {
            tokenizator->tree->var_count++;
            tokenizator->tree->variables[tokenizator->tokens[current_token].value.variable - 'A'] = 1; 
        }
        return CreateNode(NODE_VARIABLE, tokenizator->tokens[current_token++].value);
    }

    fprintf(stderr, "ERROR: Fail in Var parsing\n");
    return NULL;
}

// Проверка текущего токена на операцию
static bool CheckOperation(Tokenizator* tokenizator, Operation op)
{
    assert(tokenizator);

    if(tokenizator->tokens_count > current_token
       && tokenizator->tokens[current_token].type == NODE_OPERATION
       && tokenizator->tokens[current_token].value.operation == op) return true;

    return false;
}

// Настройка переменных в дереве
void SetupTree(Tokenizator* tokenizator)
{
    assert(tokenizator);

    Tree* tree = tokenizator->tree;
    tree->variables_offsets = (size_t*)calloc(tree->var_count, sizeof(size_t));

    size_t j = 0;

    for(size_t i = 0; i < 'Z' - 'A' + 1; i++)
    {
        if(tree->variables[i]) tree->variables_offsets[j++] = i;
    }
}

