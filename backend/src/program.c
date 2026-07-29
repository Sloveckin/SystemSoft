#include "backend/program.h"

#include "backend/common/function.h"
#include "colc/cstring.h"
#include "backend/common/signature.h"

int program_init(struct Program* program)
{
    const ObjectInfo key_info = {
        .size = sizeof(CString),
        .copy = cstring_copy,
        .destructor = cstring_free,
    };
    const ObjectInfo signature_ptr_info = {
        .size = sizeof(struct Signature*),
        .copy = NULL,
        .destructor = signature_ptr_free,
    };
    int err = map_init(&program->signatures_ptr, cstring_hash, cstring_comp, key_info, signature_ptr_info);
    if (err != 0) {
        return err;
    }

    const ObjectInfo function_ptr_info = {
        .size = sizeof(struct Function*),
        .copy = NULL,
        .destructor = function_des,
    };
    err = map_init(&program->functions_ptr, cstring_hash, cstring_comp, key_info, function_ptr_info);
    if (err != 0) {
        map_free(&program->functions_ptr);
        return err;
    }

    return 0;
}

void program_free(struct Program* program)
{
    map_free(&program->signatures_ptr);
    map_free(&program->functions_ptr);
}