#ifndef VARIABLE_H
#define VARIABLE_H

#include "backend/type/type.h"

struct Variable {
    char* name;
    enum Type type;
};

void variable_init(struct Variable* variable, char* name, const enum Type type);

void variable_free(struct Variable* variable);

int variable_copy(void* dst, const void* src);

void variable_destructor(void* variable);

#endif