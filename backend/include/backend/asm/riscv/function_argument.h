#ifndef BACKEND_ASM_RISCV_FUNCTION_ARGUMENT_H
#define BACKEND_ASM_RISCV_FUNCTION_ARGUMENT_H

#include "middleend/optree.h"

struct FunctionArgument {
    char* name;
    enum OperationNodeType type;
};

int function_argurement_init(struct FunctionArgument* func_arg, const char* name, const enum OperationNodeType type);

void function_argument_free(struct FunctionArgument* func_arg);

void function_argument_des(void* value);

#endif