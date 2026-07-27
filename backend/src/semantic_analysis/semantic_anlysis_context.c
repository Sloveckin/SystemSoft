#include "backend/common/signature.h"
#include "backend/semantic_analysis/semantic_analysis_context.h"

#include "backend/common/variable.h"
#include "colc/map.h"
#include "colc/object_info.h"

int semantic_analysis_context_init(struct SemanticAnalysisContext* ctx, Map* signatures)
{
    const ObjectInfo key_info = {
        .size = sizeof(CString),
        .copy = cstring_copy,
        .destructor = cstring_free,
    };

    const ObjectInfo value_info = {
        .size = sizeof(struct Variable),
        .copy = variable_copy,
        .destructor = variable_destructor
    };
    int err = map_init(&ctx->arguments, cstring_hash, cstring_comp, key_info, value_info);
    if (err != 0) {
        return err;
    }
    
    err = map_init(&ctx->variables, cstring_hash, cstring_comp, key_info, value_info);
    if (err != 0) {
        return err;
    }

    ctx->signatures = signatures;
    ctx->cycle_counter = 0;

    return 0;
}

struct Variable* get_variable_by_name(struct SemanticAnalysisContext* ctx, CString* name)
{
    struct Variable* variable = map_get(&ctx->arguments, name);
    if (variable != NULL) {
        return variable;
    }

    return map_get(&ctx->variables, name); 
}

struct Signature* get_signature_by_name(struct SemanticAnalysisContext* ctx, CString* name)
{
    struct Signature** pointer = map_get(ctx->signatures, name);
    if (pointer == NULL) {
        return NULL;
    }
    return *pointer;
}


void semantic_analysis_context_free(struct SemanticAnalysisContext* ctx)
{
    map_free(&ctx->arguments);
    map_free(&ctx->variables);
}
