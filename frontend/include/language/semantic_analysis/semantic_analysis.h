#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include <stdbool.h>
#include <stdint.h>

#include "language/program.h"
#include "language/type/type.h"
#include "colc/vector.h"
#include "semantic_analysis_context.h"
#include "ast/ast_node.h"
#include "language/common/function.h"

struct ExpressionInfo {
    struct Type* type;
    bool is_constant;

    union {
        int64_t number;
        uint64_t unumber;
        bool boolean;
    } value;
};
struct Type* get_type(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, int* error, bool add_to_ctx);

int semantic_function_analysis(struct Function* function, struct AstNode* node, Vector* errors, bool* error_occur, struct Program* program);

int program_semantic_analysis(struct Program* program);

#endif