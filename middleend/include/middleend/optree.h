#ifndef OPERATION_TREE_H
#define OPERATION_TREE_H

#include "ast/ast_node.h"

enum OperationNodeType {
    OP_NODE_CREATION_VARIABLE,
    OP_NODE_IDENTIFIER_LIST,
    OP_NODE_IDENTIFIER,
    OP_NODE_STORE,
    OP_NODE_STORE_ARRAY,
    OP_NODE_LOAD,
    OP_NODE_CONST,
    OP_NODE_TYPE_SHORT,
    OP_NODE_TYPE_USHORT,
    OP_NODE_TYPE_INT,
    OP_NODE_TYPE_UINT,
    OP_NODE_TYPE_LONG,
    OP_NODE_TYPE_ULONG,
    OP_NODE_TYPE_BOOL,
    OP_NODE_TYPE_ARRAY,
    OP_NODE_TYPE_STRING,
    OP_NODE_ASSIGMENT,
    OP_NODE_PLUS,
    OP_NODE_MINUS,
    OP_NODE_MUL,
    OP_NODE_DIV,
    OP_NODE_OR,
    OP_NODE_AND,
    OP_NODE_LESS,
    OP_NODE_MORE,
    OP_NODE_EQ,
    OP_NODE_NOT_EQ,
    OP_NODE_BREAK,
    OP_NODE_RETURN,
    OP_NODE_CALL_OR_INDEXER,
    OP_NODE_EXPR_LIST,
    OP_NODE_UNARY_MINUS,
    OP_NODE_UNARY_PLUS,
    OP_NODE_BOOL,
};

struct OperationTreeNode {
    enum OperationNodeType type;

    char* argument;

    Vector children;
    struct {
        int id;
        bool flag;
    } value;
};

int operation_tree_node_init(struct OperationTreeNode* node, const enum OperationNodeType type);

int operation_tree_node_init_with_argument(struct OperationTreeNode* node, const enum OperationNodeType type, const char* argument_text);

void operation_tree_free(struct OperationTreeNode* node);

void operation_tree_des(void* value);

struct OperationTreeNode* operation_tree_create(struct AstNode* node);

#endif