#include "language/common/function.h"

#include "language/common/signature.h"
#include "language/program.h"
#include "middleend/cfg_node.h"

#include <malloc.h>
#include <assert.h>

int function_init(struct Function* function, struct Program* program, struct AstNode* node)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* signature_node = *pointer;
    
    int err = signature_init(&function->signature, signature_node, program);
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
    if (function->cfg != NULL) {
        cfg_node_free(function->cfg);
    }
}

void function_des(void* value)
{
    struct Function** function = value;
    function_free(*function);
    free(*function);
}

