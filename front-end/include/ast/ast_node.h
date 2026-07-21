#ifndef AST_NODE_H
#define AST_NODE_H

#include "ast/ast_node_type.h"
#include "colc/vector.h"

struct AstNode {
    enum AstNodeType type;
    Vector children;
    char* text;
};

void ast_node_init(struct AstNode* node, const enum AstNodeType type);

int ast_node_init_with_text(struct AstNode* node, const enum AstNodeType type, const char* text);

void ast_node_destructor(void* node);

#endif