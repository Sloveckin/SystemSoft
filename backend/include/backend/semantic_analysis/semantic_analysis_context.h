#ifndef SEMANTIC_ANALYZE_CONTEXT_H
#define SEMANTIC_ANALYZE_CONTEXT_H

#include <stdbool.h>

#include "backend/program.h"
#include "colc/cstring.h"
#include "colc/map.h"

struct SemanticContext {
    struct Program *program;
    Map arguments;
    Map variables;
    int cycle_counter;
};

int semantic_analysis_context_init(struct SemanticContext* ctx, struct Program* program);

struct Variable* get_variable_by_name(struct SemanticContext* ctx, CString* name);

struct Signature* get_signature_by_name(struct SemanticContext* ctx, CString* name);

void semantic_analysis_context_free(struct SemanticContext* ctx);

#endif
