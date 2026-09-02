#include "backend/asm/riscv/asm_instruction.h"
#include "backend/asm/riscv/register.h"

#include <malloc.h>

const char* mnemonic_to_str[] = {
    "addi",
    "sb",
    "sh",
    "sw",
    "sd",
    "ld",
};

struct ITypeInstruction* itype_instruction_init(const enum Mnemonic mnemonic, const enum RegisterType r1, const enum RegisterType r2, const int64_t imm)
{
    struct ITypeInstruction* instr = malloc(sizeof(struct ITypeInstruction));
    if (instr == NULL) {
        return NULL;
    }

    instr->base.format = INSTRUCTION_FORMAT_I;
    instr->base.mnemonic = mnemonic;

    instr->r1 = r1;
    instr->r2 = r2;
    instr->imm = imm;

    return instr;
}

struct SLTypeInstruction* sltype_instruction_init(const enum Mnemonic mnemonic, const enum RegisterType r1, const enum RegisterType r2, const int64_t offset)
{
    struct SLTypeInstruction* instr = malloc(sizeof(struct SLTypeInstruction));
    if (instr == NULL) {
        return NULL;
    }

    instr->base.format = INSTRUCTION_FORMAT_S;
    instr->base.mnemonic = mnemonic;

    instr->r1 = r1;
    instr->r2 = r2;
    instr->offset = offset;

    return instr;
}

int write_inscruction(struct Instruction* instruction, FILE* file)
{
    if (instruction->format == INSTRUCTION_FORMAT_I) {
        struct ITypeInstruction* i_instruction = (struct ITypeInstruction*) instruction;
        
        int res = fprintf(file, "\t%s %s, %s, %ld\n", 
            mnemonic_to_str[i_instruction->base.mnemonic], 
            register_type_to_str[i_instruction->r1], 
            register_type_to_str[i_instruction->r2], 
            i_instruction->imm);
            
        if (res < 0) {
            return res;
        }
    } else if (instruction->format == INSTRUCTION_FORMAT_S) {
        struct SLTypeInstruction* s_instruction = (struct SLTypeInstruction*) instruction;
        int res = fprintf(file, "\t%s %s, %ld(%s)\n",
            mnemonic_to_str[s_instruction->base.mnemonic],
            register_type_to_str[s_instruction->r1],
            s_instruction->offset,
            register_type_to_str[s_instruction->r2]
        );

        if (res < 0) {
            return res;
        }
    }

    return 0;
}