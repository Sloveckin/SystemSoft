#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "../type/type.h"
#include "ast/ast_node.h"

struct Signature {
    char* name;
    enum Type return_type;
    Vector arguments;

    // Don't need to clean it
    struct AstNode* ast;
};

int signature_init(struct Signature* signature, struct AstNode* node);

void signature_free(struct Signature* signature);

void signature_ptr_free(void* value);

#endif