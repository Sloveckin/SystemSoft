#include "backend/asm/riscv/asm_line.h"
#include "backend/asm/riscv/asm_directive.h"
#include "backend/asm/riscv/asm_instruction.h"

#include <malloc.h>
#include <assert.h>

void riscv_line_free(void* value)
{
    struct RiscVLine* line = value;
    if (line->type == LINE_TYPE_INSTRUCTION) {
        free_instruction(line->instruction);
        free(line->instruction);
    } else if (line->type == LINE_TYPE_LABEL) {
        free(line->text);
    } else if (line->type == LINE_TYPE_DIRECTIVE) {
        directive_free(line->directive);
        free(line->directive);
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
    } else if (line->type == LINE_TYPE_DIRECTIVE) {
        return write_directive(line->directive, file);
    } else {
        assert(0);
    }

    return 0;
}