#ifndef RISC_V_ASM_GENERATOR
#define RISC_V_ASM_GENERATOR

#include "backend/asm/riscv/machine.h"

#include "colc/map.h"
#include "middleend/cfg_node.h"
#include "colc/linked_list.h"
#include "colc/stack.h"

struct RiscVContext {
    struct RiscVMachine machine;
    Stack register_stack;
    LinkedList instruction_list;
    Map stack_recording;
    size_t stack_size;
};

int risc_v_context_init(struct RiscVContext* ctx);

void risc_v_context_free(struct RiscVContext* ctx);

int risc_v_generate_asm(struct CfgNode* cfg_node, struct RiscVContext* ctx);


#endif