#include "backend/asm/riscv/asm_line.h"
#include "backend/asm/riscv/asm_instruction.h"

#include <malloc.h>

void riscv_line_free(void* value)
{
    struct RiscVLine* line = value;
    if (line->type == LINE_TYPE_INSTRUCTION) {
        free(line->instruction);
    } else if (line->type == LINE_TYPE_LABEL) {
        free(line->text);
    }
}

int write_riscv_line(const struct RiscVLine* line, FILE* file)
{
    if (line->type == LINE_TYPE_INSTRUCTION) {
        return write_inscruction(line->instruction, file);
    } else if (line->type == LINE_TYPE_LABEL) {
        int res = fprintf(file, "%s:\n", line->text);
        if (res < 0) {
            return -1;
        }

        return 0;
    }

    return 0;
}