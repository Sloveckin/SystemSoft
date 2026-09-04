#include "language/common/function.h"

#include "backend/asm/riscv/asm_generator.h"
#include "language/common/signature.h"
#include "language/program.h"
#include "middleend/cfg_context.h"

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

    err = cfg_context_init(&function->cfg_context);
    if (err != 0) {
        return err;
    }

    function->ast = node;
    function->cfg = NULL;
    function->riscv_context = NULL;

    return 0;
}

void function_free(struct Function* function)
{
    if (function->riscv_context != NULL) {
        risc_v_context_free(function->riscv_context);
    }
    free(function->riscv_context);
    signature_free(&function->signature);
    cfg_context_free(&function->cfg_context);
}

void function_des(void* value)
{
    struct Function** function = value;
    function_free(*function);
    free(*function);
}
