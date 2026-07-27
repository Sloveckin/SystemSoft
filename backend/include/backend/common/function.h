#ifndef BACKEND_FUNCTION_H
#define BACKEND_FUNCTION_H

#include "../cfg/control_flow_graph_node.h"
#include "ast/ast_node.h"
#include "signature.h"

struct Function {
    struct Signature* signature;
    struct CfgNode* cfg;
};

int function_init(struct Function* function, struct AstNode* node, struct Signature* signature);

void function_free(struct Function* function);

#endif