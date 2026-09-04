#include "language/program.h"

#include "language/common/function.h"
#include "colc/cstring.h"
#include "language/common/signature.h"
#include "backend/asm/riscv/asm_generator.h"

#include <malloc.h>

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

int program_generate_asm(struct Program* program)
{
    for (size_t i = 0; i < program->functions_ptr.capacity; i++) {
        if (program->functions_ptr.buffer[i].key == NULL) {
            continue;
        }

        struct Function** pointer = program->functions_ptr.buffer[i].value;
        struct Function* function = *pointer;

        struct RiscVContext* ctx = malloc(sizeof(struct RiscVContext));
        if (ctx == NULL) {
            return -1;
        }

        int err = risc_v_context_init(ctx);
        if (err != 0) {
            risc_v_context_free(ctx);
            return err;
        }

        
        err = risc_v_generate_asm(function->signature.name, function->cfg, ctx);
        if (err) {
            risc_v_context_free(ctx);
            return err;
        }

        if (strcmp(function->signature.name, "main") == 0) {
            err = generate_start_position(ctx);
            if (err != 0) {
                return err;
            }
        }

        function->riscv_context = ctx;
    }

    return 0;
}
