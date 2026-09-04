#ifndef BACKEND_ASM_RISCV_ASM_LINE
#define BACKEND_ASM_RISCV_ASM_LINE

#include "backend/asm/riscv/asm_directive.h"
#include "backend/asm/riscv/asm_instruction.h"

enum RiscVLineType {
    LINE_TYPE_INSTRUCTION,
    LINE_TYPE_LABEL,
    LINE_TYPE_DIRECTIVE,
};

struct RiscVLine {
    enum RiscVLineType type;
    union {
        struct Instruction* instruction;
        struct Directive* directive;
        char* text;
    };
};

void riscv_line_free(void* value);

int write_riscv_line(const struct RiscVLine* line, FILE* file);

#endif