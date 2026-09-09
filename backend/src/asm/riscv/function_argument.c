#include "backend/asm/riscv/function_argument.h"

#include <malloc.h>

int function_argurement_init(struct FunctionArgument* arg, const char* name, const enum OperationNodeType type)
{
    const size_t name_length = strlen(name) + 1;
    arg->name = malloc(name_length * sizeof(char));
    if (arg->name == NULL) {
        return -1;
    }

    strcpy(arg->name, name);
    arg->type = type;

    return 0;
}

void function_argument_free(struct FunctionArgument* func_arg)
{
    free(func_arg->name);
}

void function_argument_des(void* value)
{
    struct FunctionArgument* arg = value;
    function_argument_free(arg);
}