#include <stdlib.h>

#include "tree.h"
#include "assert.h"

Tree* CreateTree()
{
    Tree* tree = (Tree*)calloc(1, sizeof(Tree));
    if(!tree) return NULL;
}

void DestroyTree(Tree* tree)
{
    if(!tree) return;

    DestroyNode(tree->root);

    free(tree);
}

void DestroyNode(TreeNode* node)
{
    if(!node) return;

    DestroyNode(node->left);
    DestroyNode(node->right);

    free(node);
}

TreeNode* CreateNode(NodeType type, NodeValue value)
{
    TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode));
    if(!node) return NULL;

    node->type = type;
    node->value = value;
}

