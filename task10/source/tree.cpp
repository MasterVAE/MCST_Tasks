#include <stdlib.h>

#include "tree.h"
#include "assert.h"

// Инициализация дерева
Tree* CreateTree()
{
    Tree* tree = (Tree*)calloc(1, sizeof(Tree));
    if(!tree) return NULL;

    return tree;
}

// Уничтожение дерева
void DestroyTree(Tree* tree)
{
    if(!tree) return;

    DestroyNode(tree->root);

    free(tree->variables_offsets);
    free(tree);
}

// Уничтожение ноды
void DestroyNode(TreeNode* node)
{
    if(!node) return;

    DestroyNode(node->left);
    DestroyNode(node->right);

    free(node);
}

// Инициализация ноды
TreeNode* CreateNode(NodeType type, NodeValue value)
{
    TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode));
    if(!node) return NULL;

    node->type = type;
    node->value = value;

    return node;
}

