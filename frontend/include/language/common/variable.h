#ifndef VARIABLE_H
#define VARIABLE_H

#include "language/type/type.h"

struct Variable {
    char* name;
    struct Type* type;
};

void variable_init(struct Variable* variable, char* name, struct Type* type);

void variable_free(struct Variable* variable);

int variable_copy(void* dst, const void* src);

void variable_destructor(void* variable);

#endif