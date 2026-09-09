#include "language/program.h"

#include "backend/asm/riscv/function_argument.h"
#include "backend/asm/riscv/label_generator.h"
#include "colc/object_info.h"
#include "colc/vector.h"
#include "language/common/function.h"
#include "colc/cstring.h"
#include "language/common/signature.h"
#include "backend/asm/riscv/asm_generator.h"
#include "language/common/variable.h"
#include "language/type/type.h"
#include "middleend/optree.h"

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

static int prepare_arguments(Vector* from, Vector* to)
{
    for (size_t i = 0; i < from->size; i++) {
        const struct Variable* var = vector_get(from, i);
        struct FunctionArgument func_arguemnt;

        enum OperationNodeType type;
        if (var->type->kind == TYPE_KIND_BOOL) {
            type = OP_NODE_TYPE_BOOL;
        } else if (var->type->kind == TYPE_KIND_INT) {
            type = OP_NODE_TYPE_INT;
        } else if (var->type->kind == TYPE_KIND_UINT) {
            type = OP_NODE_TYPE_UINT;
        }

        int err = function_argurement_init(&func_arguemnt, var->name, type);
        if (err != 0) {
            return err;
        }

        err = vector_push(to, &func_arguemnt);
        if (err != 0) {
            return err;
        }
    }

    return 0;
}

int program_generate_asm(struct Program* program)
{
    struct LabelGenerator label_generator;
    label_generator_init(&label_generator);

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

        int err = risc_v_context_init(ctx, &label_generator);
        if (err != 0) {
            risc_v_context_free(ctx);
            return err;
        }

        const ObjectInfo info = {
            .size = sizeof(struct FunctionArgument),
            .copy = NULL,
            .destructor = function_argument_des,
        };
        Vector arguments;
        err = vector_init(&arguments, info);
        if (err != 0) {
            risc_v_context_free(ctx);
            return err;
        }

        err = prepare_arguments(&function->signature.arguments, &arguments);
        if (err != 0) {
            vector_free(&arguments);
            risc_v_context_free(ctx);
            return err;
        }

        err = risc_v_generate_asm(function->signature.name, function->cfg, &arguments, ctx);
        if (err) {
            vector_free(&arguments);
            risc_v_context_free(ctx);
            return err;
        }
        vector_free(&arguments);


        if (strcmp(function->signature.name, "main") == 0) {
            err = generate_start_position(ctx);
            if (err != 0) {
                risc_v_context_free(ctx);
                return err;
            }
        }

        function->riscv_context = ctx;
    }

    return 0;
}
