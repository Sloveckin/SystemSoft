#ifndef PARSER_H
#define PARSER_H

#include "../ast/ast_node.h"

#include <stdio.h>

struct AstNode* parse(FILE* file);

#endif