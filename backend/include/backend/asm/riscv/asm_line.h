#ifndef BACKEND_ASM_RISCV_ASM_LINE
#define BACKEND_ASM_RISCV_ASM_LINE

#include "backend/asm/riscv/asm_instruction.h"

enum RiscVLineType {
    LINE_TYPE_INSTRUCTION,
};

struct RiscVLine {
    enum RiscVLineType type;
    union {
        struct Instruction* instruction;
    };
};

void riscv_line_free(void* value);

#endif