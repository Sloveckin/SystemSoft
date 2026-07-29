#ifndef BACKEND_FUNCTION_H
#define BACKEND_FUNCTION_H

#include "../cfg/control_flow_graph_node.h"
#include "backend/semantic_analysis/semantic_analysis_context.h"
#include "signature.h"

struct Function {
    struct Signature signature;
    struct SemanticContext* semantic_context;
    struct AstNode *ast;
    struct CfgNode* cfg;
};

int function_init(struct Function* function, struct AstNode* node);

void function_free(struct Function* function);

void function_des(void* function);

#endif