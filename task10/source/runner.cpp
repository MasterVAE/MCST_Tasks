#include <assert.h>
#include <stdio.h>

#include "runner.h"
#include "tree.h"

static void RunNode(Tree* tree, TreeNode* node);

void Run(Tree* tree)
{
    assert(tree);

    for(size_t i = 0; i < tree->var_count; i++)
    {
        printf("%c ", 'A' + (char)tree->variables_offsets[i]);
    }
    printf("Result\n");

    for(size_t i = 0; i < (size_t)(1 << tree->var_count); i++)
    {
        for(size_t j = 0; j < tree->var_count; j++)
        {
            tree->variables_values[tree->variables_offsets[j]] = (i >> (tree->var_count - j - 1))&1;
            printf("%d ", (int)(i >> (tree->var_count - j - 1))&1);
        }

        RunNode(tree, tree->root);
        printf("%d\n", tree->root->bool_value);
    }
}

static void RunNode(Tree* tree, TreeNode* node)
{
    assert(tree);

    if(!node) return;

    RunNode(tree, node->left);
    RunNode(tree, node->right);

    if(node->type == NODE_VARIABLE)
    {
        node->bool_value = tree->variables_values[node->value.variable - 'A'];
        return;
    }
    
    if(node->value.operation == OP_AND)
    {
        node->bool_value = node->left->bool_value & node->right->bool_value;
    }
    else if(node->value.operation == OP_OR)
    {
        node->bool_value = node->left->bool_value | node->right->bool_value;
    }
    else
    {
        node->bool_value = !node->left->bool_value;
    }
}