#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "ast/ast_node.h"
#include "backend/semantic_analysis/semantic_analysis_context.h"
#include "colc/vector.h"

int semantic_analysis(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx);

#endif