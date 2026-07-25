#ifndef SEMANTIC_ANALYZE_CONTEXT_H
#define SEMANTIC_ANALYZE_CONTEXT_H

#include "colc/map.h"


struct SemanticAnalysisContext {
    Map arguments;
    Map variables;
};

int semantic_analysis_context_init(struct SemanticAnalysisContext* ctx);

void semantic_analysis_context_free(struct SemanticAnalysisContext* ctx);

#endif