#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "ast/ast_node.h"
#include "backend/common/signature.h"
#include "backend/common/function.h"
#include "backend/semantic_analysis/semantic_analysis_context.h"
#include "colc/vector.h"

//int semantic_signature_analysis(struct Signature* signature, struct AstNode* node, Vector* errors, struct SemanticContext* ctx);

//int semantic_function_analysis(struct Function* function, struct AstNode* node, Vector* errors);

int program_semantic_analysis(struct Program* program);

#endif