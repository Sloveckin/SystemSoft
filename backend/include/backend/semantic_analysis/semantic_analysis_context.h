#ifndef SEMANTIC_ANALYZE_CONTEXT_H
#define SEMANTIC_ANALYZE_CONTEXT_H

#include <stdbool.h>

#include "colc/cstring.h"
#include "colc/map.h"

struct SemanticAnalysisContext {
    Map *signatures;
    Map arguments;
    Map variables;
    int cycle_counter;
};

int semantic_analysis_context_init(struct SemanticAnalysisContext* ctx, Map* signatures);

struct Variable* get_variable_by_name(struct SemanticAnalysisContext* ctx, CString* name);

struct Signature* get_signature_by_name(struct SemanticAnalysisContext* ctx, CString* name);

void semantic_analysis_context_free(struct SemanticAnalysisContext* ctx);

#endif
