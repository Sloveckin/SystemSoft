#ifndef BACKEND_FUNCTION_H
#define BACKEND_FUNCTION_H

#include "backend/asm/riscv/asm_generator.h"
#include "language/program.h"
#include "language/semantic_analysis/semantic_analysis_context.h"
#include "middleend/cfg_context.h"
#include "signature.h"


struct Function {
    struct Signature signature;
    struct AstNode* ast;

    struct CfgContext cfg_context;
    struct CfgNode* cfg;
    
    struct RiscVContext* riscv_context;
};

int function_init(struct Function* function, struct Program* program, struct AstNode* node);

void function_free(struct Function* function);

void function_des(void* function);

#endif