#include "language/semantic_analysis/semantic_analysis_context.h"

#include <malloc.h>

#include "language/common/signature.h"
#include "language/common/function.h"
#include "language/program.h"
#include "language/common/variable.h"
#include "language/type/type.h"
#include "colc/map.h"
#include "colc/object_info.h"

int semantic_analysis_context_init(struct SemanticContext* ctx, struct Program* program)
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

    const ObjectInfo type_ptr_info = {
        .size = sizeof(struct Type*),
        .copy = NULL,
        .destructor = type_ptr_des,
    };
    err = vector_init(&ctx->types, type_ptr_info);
    if (err != 0) {
        return err;
    }

    ctx->program = program;
    ctx->cycle_counter = 0;

    return 0;
}

struct Variable* get_variable_by_name(struct SemanticContext* ctx, CString* name)
{
    struct Variable* variable = map_get(&ctx->arguments, name);
    if (variable != NULL) {
        return variable;
    }

    return map_get(&ctx->variables, name); 
}

struct Signature* get_signature_by_name(struct SemanticContext* ctx, CString* name)
{
    struct Signature** pointer = map_get(&ctx->program->signatures_ptr, name);
    if (pointer != NULL) {
        return *pointer;
    }
    struct Function** function = map_get(&ctx->program->functions_ptr, name);
    if (function == NULL) {
        return NULL;
    }
    return &(*function)->signature;
}

void semantic_analysis_context_free(struct SemanticContext* ctx)
{
    map_free(&ctx->arguments);
    map_free(&ctx->variables);
    vector_free(&ctx->types);
}
