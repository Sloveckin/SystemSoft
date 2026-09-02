#include "backend/asm/riscv/asm_generator.h"

#include "backend/asm/riscv/asm_instruction.h"
#include "backend/asm/riscv/asm_line.h"
#include "backend/asm/riscv/machine.h"
#include "backend/asm/riscv/register.h"
#include "backend/asm/riscv/stack_recording.h"
#include "colc/cstring.h"
#include "colc/linked_list.h"
#include "colc/map.h"
#include "colc/object_info.h"
#include "colc/stack.h"
#include "middleend/optree.h"

#include <endian.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

static size_t size_of_type(const enum OperationNodeType type) {
    if (type == OP_NODE_TYPE_INT || type == OP_NODE_TYPE_UINT) {
        return INT_SIZE;
    } else if (type == OP_NODE_TYPE_SHORT || type == OP_NODE_TYPE_USHORT) {
        return SHORT_SIZE;
    } else if (type == OP_NODE_TYPE_LONG || type == OP_NODE_TYPE_ULONG) {
        return LONG_SIZE;
    } else if (type == OP_NODE_TYPE_BOOL) {
        return BOOL_SIZE;
    }

    assert (0);
}

static enum Mnemonic store_mnemonic_by_size(const size_t size)
{
    if (size == BOOL_SIZE) {
        return MN_SB;
    } else if (size == SHORT_SIZE) {
        return MN_SH;
    } else if (size == INT_SIZE) {
        return MN_SW;
    } else if (size == LONG_SIZE) {
        return MN_SD;
    }

    assert(0);
}

static int load_const(struct OperationTreeNode* node, struct RiscVContext* ctx)
{
    struct Register* reg = riscv_machine_get_temp_register(&ctx->machine);
    if (reg == NULL) {
        puts("Couldn't find free register, please rewrite your code");
        return -1;
    }
    reg->used = true;

    int64_t imm;
    if (strcmp(node->argument, "true") == 0) {
        imm = 1;
    } else if (strcmp(node->argument, "false") == 0) {
        imm = 0;
    } else {
        // Yes, I can use atoi, because node->argument has valid value
        imm = atoi(node->argument);
    }

    struct ITypeInstruction* addi = itype_instruction_init(MN_ADDI, ZERO, reg->type, imm);
    if (addi == NULL) {
        return -1;
    }

    struct RiscVLine line = {
        .type = LINE_TYPE_INSTRUCTION,
        .instruction = (struct Instruction*) addi,
    };

    int err = linked_push_back(&ctx->instruction_list, &line);
    if (err != 0) {
        free(addi);
        return err;
    }

    err = stack_push(&ctx->register_stack, &reg->type);
    if (err != 0) {
        free(addi);
        return err;
    }

    return 0;
}

static int load(struct OperationTreeNode* node, struct RiscVContext* ctx)
{
    if (node->type == OP_NODE_CONST) {
        return load_const(node, ctx);
    } else {
        assert(0);
    }

    return 0;
}

static int store(struct OperationTreeNode* node, struct RiscVContext* ctx)
{
    CString variable_name;
    int err = cstring_init(&variable_name, node->argument);
    if (err != 0) {
        return err;
    }
    // Checking is useless, because recording exists in map
    const struct StackRecording* recoring = map_get(&ctx->stack_recording, &variable_name);

    const enum RegisterType* reg = stack_top(&ctx->register_stack);
    stack_pop(&ctx->register_stack);
    ctx->machine.registers[*reg].used = false;

    const enum Mnemonic store_mnemonic = store_mnemonic_by_size(recoring->size);
    struct SLTypeInstruction* save_instruction = sltype_instruction_init(store_mnemonic, *reg, REGISTER_VARIABLE_MAPPING, recoring->offset);
    if (save_instruction == NULL) {
        cstring_free(&variable_name);
        return -1;
    }

    struct RiscVLine line = {
        .type = LINE_TYPE_INSTRUCTION,
        .instruction = (struct Instruction*) save_instruction,
    };

    err = linked_push_back(&ctx->instruction_list, &line);
    if (err != 0) {
        cstring_free(&variable_name);
    }

    cstring_free(&variable_name);
    return 0;
}

static int generate_creation_variable(struct OperationTreeNode* node, struct RiscVContext* ctx)
{
    struct OperationTreeNode** pointer = vector_get(&node->children, 0);
    struct OperationTreeNode* variables = *pointer;

    pointer = vector_get(&node->children, 1);
    struct OperationTreeNode* type = *pointer;

    const size_t type_size = size_of_type(type->type);

    for (size_t i = 0; i < variables->children.size; i++) {
        pointer = vector_get(&variables->children, i);
        struct OperationTreeNode* variable_node = *pointer;

        CString variable_name;
        int err = cstring_init(&variable_name, variable_node->argument);
        if (err != 0) {
            return err;
        }
        
        struct StackRecording stack_recording = {
            .size = type_size,
            .offset = ctx->stack_size,
        };
        ctx->stack_size += type_size;

        err = map_insert(&ctx->stack_recording, &variable_name, &stack_recording);
        if (err != 0) {
            cstring_free(&variable_name);
            return err;
        }

        cstring_free(&variable_name);
    }

    return 0;
}

static int generate_assigment(struct OperationTreeNode* node, struct RiscVContext* ctx)
{
    struct OperationTreeNode** pointer = vector_get(&node->children, 0);
    struct OperationTreeNode* left_node = *pointer;

    pointer = vector_get(&node->children, 1);
    struct OperationTreeNode* right_node = *pointer;

    int err = load(right_node, ctx);
    if (err != 0) {
        return err;
    }

    err = store(left_node, ctx);
    if (err != 0) {
        return err;
    }

    return 0;
}

static int cfg_generate(struct CfgNode* cfg_node, struct RiscVContext* ctx)
{
    if (cfg_node == NULL || cfg_node->asm_data.asm_generated == true) {
        return 0;
    }

    cfg_node->asm_data.asm_generated = true;

    if (cfg_node->operation_node->type == OP_NODE_CREATION_VARIABLE) {
        int err =  generate_creation_variable(cfg_node->operation_node, ctx);
        if (err != 0) {
            return err;
        }
    } else if(cfg_node->operation_node->type == OP_NODE_ASSIGMENT) {
        int err = generate_assigment(cfg_node->operation_node, ctx);
        if (err != 0) {
            return err;
        }
    } else {
        assert(0);
    }

    int err = cfg_generate(cfg_node->def, ctx);
    if (err != 0) {
        return err;
    }

    return cfg_generate(cfg_node->condition, ctx);
}

static int generate_prolog(struct RiscVContext* ctx)
{
    struct SLTypeInstruction* save_ra = sltype_instruction_init(MN_SD, RA, SP, ctx->stack_size);
    if (save_ra == NULL) {
        return -1;
    }

    struct Register* ra_register = &ctx->machine.registers[RA];
    ra_register->used = true;
    ra_register->offset = ctx->stack_size;

    const struct RiscVLine save_ra_line = {
        .type = LINE_TYPE_INSTRUCTION,
        .instruction = (struct Instruction*) save_ra,
    };

    int err = linked_push_front(&ctx->instruction_list, &save_ra_line);
    if (err != 0) {
        free(save_ra);
        return err;
    }

    ctx->stack_size += 8;
    struct ITypeInstruction* add_stack_frame = itype_instruction_init(MN_ADDI, SP,  SP, -ctx->stack_size);
    if  (add_stack_frame == NULL) {
        free(save_ra);
        return -1;
    }

    const struct RiscVLine grow_stack_line = {
        .type = LINE_TYPE_INSTRUCTION,
        .instruction = (struct Instruction*) add_stack_frame, 
    };

    err = linked_push_front(&ctx->instruction_list, &grow_stack_line);
    if (err != 0) {
        free(save_ra);
        free(add_stack_frame);
        return -1;
    }

    return 0;
}

static int generate_lable(const char* function_name, struct RiscVContext* ctx)
{
    const size_t label_text_length = strlen(function_name) + 1;
    char* label_text = malloc(label_text_length * sizeof(char));
    if (label_text == NULL) {
        return -1;
    }
    strcpy(label_text, function_name);

    const struct RiscVLine lable_line = {
        .type = LINE_TYPE_LABEL,
        .text = label_text,
    };

    int err = linked_push_front(&ctx->instruction_list, &lable_line);
    if (err != 0) {
        free(label_text);
        return err;
    }

    return 0;
}

static int generate_epilog(struct RiscVContext* ctx)
{
    struct Register* ra_register = &ctx->machine.registers[RA];
    struct SLTypeInstruction* load_ra = sltype_instruction_init(MN_LD, RA, SP, ra_register->offset);
    if (load_ra == NULL) {
        return -1;
    }
    ra_register->used = false;

    const struct RiscVLine load_ra_line = {
        .type = LINE_TYPE_INSTRUCTION,
        .instruction = (struct Instruction*) load_ra,
    };

    int err = linked_push_back(&ctx->instruction_list, &load_ra_line);
    if (err != 0) {
        free(load_ra);
        return err;
    }

    struct ITypeInstruction* addi = itype_instruction_init(MN_ADDI, SP, SP, ctx->stack_size);
    if (addi == NULL) {
        free(load_ra);
        return -1;
    }

     const struct RiscVLine addi_line = {
        .type = LINE_TYPE_INSTRUCTION,
        .instruction = (struct Instruction*) addi,
    };

    err = linked_push_back(&ctx->instruction_list, &addi_line);
    if (err != 0) {
        free(addi);
        free(load_ra);
        return -1;
    }
    
    return 0;
}

int risc_v_generate_asm(const char* funciton_name, struct CfgNode* cfg_node, struct RiscVContext* ctx)
{
    int err = cfg_generate(cfg_node, ctx);
    if (err != 0) {
        return err;
    }

    err = generate_prolog(ctx);
    if (err != 0) {
        return err;
    }

    err = generate_lable(funciton_name, ctx);
    if (err != 0) {
        return err;
    }

    err = generate_epilog(ctx);
    if (err != 0) {
        return err;
    }

    return 0;
}

int risc_v_context_init(struct RiscVContext* ctx)
{
    riscv_machine_init(&ctx->machine);

    const ObjectInfo register_info = {
        .size = sizeof(enum RegisterType),
        .copy = NULL,
        .destructor = NULL,
    };

    int err = stack_init(&ctx->register_stack, register_info);
    if (err != 0) {
        return err;
    }

    const ObjectInfo line_info = {
        .size = sizeof(struct RiscVLine),
        .copy = NULL,
        .destructor = riscv_line_free,
    };

    err = init_linked_list(&ctx->instruction_list, line_info);
    if (err != 0) {
        stack_free(&ctx->register_stack);
        return err;
    }

    const ObjectInfo key_info = {
        .size = sizeof(CString),
        .copy = cstring_copy,
        .destructor = cstring_free,
    };

    const ObjectInfo value_info = {
        .size = sizeof(struct StackRecording),
        .copy = NULL,
        .destructor = NULL,
    };

    err = map_init(&ctx->stack_recording, cstring_hash, cstring_comp, key_info, value_info);
    if (err != 0) {
        stack_free(&ctx->register_stack);
        linked_free(&ctx->instruction_list);
        return 0;
    }

    ctx->stack_size = 0;

    return 0;
}

void risc_v_context_free(struct RiscVContext* ctx)
{
    linked_free(&ctx->instruction_list);
    stack_free(&ctx->register_stack);
    map_free(&ctx->stack_recording);
}
