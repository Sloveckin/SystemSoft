#include "backend/asm/riscv/asm_line.h"

#include <malloc.h>

void riscv_line_free(void* value)
{
    struct RiscVLine* line = value;
    if (line->type == LINE_TYPE_INSTRUCTION) {
        free(line->instruction);
    }
}