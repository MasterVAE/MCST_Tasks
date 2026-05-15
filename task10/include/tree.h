#ifndef TREE_H
#define TREE_H

enum NodeType
{
    NODE_OPERATION,
    NODE_VARIABLE
};

enum Operation
{
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_BRACKET_OPEN,
    OP_BRACKET_CLOSE
};

union NodeValue
{
    char variable;
    Operation operation;
};


struct TreeNode
{
    NodeType type;
    NodeValue value;

    TreeNode* left;
    TreeNode* right;

    bool bool_value;
};

struct Tree
{
    TreeNode* root;

    size_t var_count;
};

Tree* CreateTree();

void DestroyTree(Tree* tree);

TreeNode* CreateNode(NodeType type, NodeValue value);

void DestroyNode(TreeNode* node);

#endif // TREE_H