#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "../type/type.h"
#include "ast/ast_node.h"
#include "backend/semantic_analysis/semantic_analysis_context.h"

struct Signature {
    char* name;
    struct Type* return_type;
    Vector arguments;

    struct SemanticContext* semantic_context;

    // Don't need to clean it
    struct AstNode* ast;
};

int signature_init(struct Signature* signature, struct AstNode* node, struct Program* program);

void signature_free(struct Signature* signature);

void signature_ptr_free(void* value);

#endif