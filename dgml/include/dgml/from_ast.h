#ifndef DGML_FROM_AST_H
#define DGML_FROM_AST_H

#include <stdio.h>

#include "ast/ast_node.h"

int from_ast_to_dgml(struct AstNode* node, FILE* file);

#endif