#ifndef OPTREE_NODE_H
#define OPTREE_NODE_H

#include "ast/ast_node.h"
#include "colc/vector.h"

enum OperationTreeNodeType {
    OP_TREE_NODE_TYPE_ASSIGMENT = 0,
    OP_TREE_NODE_TYPE_STORE = 1,
    OP_TREE_NODE_TYPE_LOAD = 2,
};

struct OperationTreeNode {
    enum OperationTreeNodeType type;
    union {
        Vector children;
        char* argument;
    } data;
};

int operation_tree_node_init(struct OperationTreeNode* node, const enum OperationTreeNodeType type);

int operation_tree_node_list_init(struct OperationTreeNode* node, const enum OperationTreeNodeType type, const char* argument);

struct OperationTreeNode* opeartion_tree_create(struct AstNode* ast_node);

void operation_tree_node_free(struct OperationTreeNode* node);

#endif