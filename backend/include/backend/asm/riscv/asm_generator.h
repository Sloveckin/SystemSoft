#ifndef RISC_V_ASM_GENERATOR
#define RISC_V_ASM_GENERATOR

#include "backend/asm/riscv/machine.h"

#include "colc/map.h"
#include "middleend/cfg_node.h"
#include "colc/linked_list.h"
#include "colc/stack.h"

#define BOOL_SIZE 1
#define SHORT_SIZE 2
#define INT_SIZE 4
#define LONG_SIZE 8

#define REGISTER_VARIABLE_MAPPING SP

struct RiscVContext {
    struct RiscVMachine machine;
    Stack register_stack;
    LinkedList instruction_list;
    Map stack_recording;
    size_t stack_size;
};

int risc_v_context_init(struct RiscVContext* ctx);

void risc_v_context_free(struct RiscVContext* ctx);

int risc_v_generate_asm(const char* function_name, struct CfgNode* cfg_node, struct RiscVContext* ctx);


#endif