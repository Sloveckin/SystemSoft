#ifndef OPERATION_TREE_H
#define OPERATION_TREE_H

#include "ast/ast_node.h"

enum OperationNodeType {
    OP_NODE_CREATION_VARIABLE,
};

struct OperationTreeNode {
    enum OperationNodeType type;

    char* argument;
};

void operation_tree_node_init(struct OperationTreeNode* node, const enum OperationNodeType type);

int operation_tree_node_init_with_argument(struct OperationTreeNode* node, const enum OperationNodeType type, const char* argument_text);

struct OperationTreeNode* operation_tree_create(struct AstNode* node);

#endif