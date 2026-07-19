#ifndef AST_NODE_H
#define AST_NODE_H

#include "colc/vector.h"

enum AstNodeType {
    AST_TYPE_DEC,
    AST_TYPE_BOOL,
    AST_TYPE_STR,
    AST_TYPE_HEX,
    AST_TYPE_BITS,
};

struct AstNode {
    enum AstNodeType type;
    Vector children;
};

void ast_node_init(struct AstNode* node, const enum AstNodeType type);

void ast_node_destructor(struct AstNode* node);

#endif