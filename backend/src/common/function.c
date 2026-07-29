#include "backend/common/function.h"

#include "backend/cfg/control_flow_graph_node.h"
#include "backend/common/signature.h"
#include "backend/semantic_analysis/semantic_analysis_context.h"

#include <malloc.h>
#include <assert.h>

int function_init(struct Function* function, struct AstNode* node)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* signature_node = *pointer;

    int err = signature_init(&function->signature, signature_node);
    if (err != 0) {
        return err;
    }

    function->ast = node;
    function->cfg = NULL;

    return 0;
}

void function_free(struct Function* function)
{
    signature_free(&function->signature);
    semantic_analysis_context_free(function->semantic_context);
    free(function->semantic_context);
    if (function->cfg) {
        control_graph_free(function->cfg);
    }
    free(function);
}

void function_des(void* value)
{
    struct Function** function = value;
    function_free(*function);
}

