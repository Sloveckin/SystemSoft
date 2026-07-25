#include "backend/common/variable.h"
#include "backend/semantic_analysis/semantic_analysis_context.h"
#include "colc/cstring.h"
#include "colc/map.h"
#include "colc/object_info.h"

int semantic_analysis_context_init(struct SemanticAnalysisContext* ctx)
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

    return 0;
}

void semantic_analysis_context_free(struct SemanticAnalysisContext* ctx)
{
    map_free(&ctx->arguments);
    map_free(&ctx->variables);
}