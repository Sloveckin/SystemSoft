#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include <stdbool.h>

#include "backend/program.h"
#include "backend/type/type.h"

//int semantic_signature_analysis(struct Signature* signature, struct AstNode* node, Vector* errors, struct SemanticContext* ctx);

//int semantic_function_analysis(struct Function* function, struct AstNode* node, Vector* errors);

struct ExpressionInfo {
    struct Type* type;
    bool can_be_compute_in_compile_time;
};

int program_semantic_analysis(struct Program* program);

#endif