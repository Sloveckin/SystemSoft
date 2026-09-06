#include "backend/asm/riscv/asm_instruction.h"
#include "backend/asm/riscv/register.h"

#include <assert.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>

const char* mnemonic_to_str[] = {
    "addi",
    "sb",
    "sh",
    "sw",
    "sd",
    "ld",
    "jal",
    "jalr",
    "lb",
    "lh",
    "lw",
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
    instr->base.free_function = NULL;

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
    instr->base.free_function = NULL;

    return instr;
}

int write_inscruction(struct Instruction* instruction, FILE* file)
{
    int res = 0;
    if (instruction->format == INSTRUCTION_FORMAT_I) {
        struct ITypeInstruction* i_instruction = (struct ITypeInstruction*) instruction;
        
        res = fprintf(file, "\t%s %s, %s, %ld\n", 
            mnemonic_to_str[i_instruction->base.mnemonic], 
            register_type_to_str[i_instruction->r1], 
            register_type_to_str[i_instruction->r2], 
            i_instruction->imm);
    } else if (instruction->format == INSTRUCTION_FORMAT_S) {
        struct SLTypeInstruction* s_instruction = (struct SLTypeInstruction*) instruction;
        int res = fprintf(file, "\t%s %s, %ld(%s)\n",
            mnemonic_to_str[s_instruction->base.mnemonic],
            register_type_to_str[s_instruction->r1],
            s_instruction->offset,
            register_type_to_str[s_instruction->r2]
        );
    } else if (instruction->format == INSTCURTION_FORMAT_JAL) {
        struct JalInstruction* jal = (struct JalInstruction*) instruction;
        res = fprintf(file, "\t%s %s, %s\n", mnemonic_to_str[jal->base.mnemonic], register_type_to_str[jal->reg], jal->label);
    } else {
        assert(0);
    }

    if (res < 0) {
        return res;
    }

    return 0;
}

static void jal_instruction_free(struct Instruction* instr) {
    free(((struct JalInstruction*)instr)->label);
}

struct JalInstruction* jal_instructoin_init(const enum RegisterType reg, const char* text)
{
    struct JalInstruction* instr = malloc(sizeof(struct JalInstruction));
    if (instr == NULL) {
        return NULL;
    }

    const size_t label_length = strlen(text) + 1;
    instr->label = malloc(label_length * sizeof(char));
    if (instr->label == NULL) {
        free(instr);
        return NULL;
    }
    strcpy(instr->label, text);

    instr->base.format = INSTCURTION_FORMAT_JAL;
    instr->base.mnemonic = MN_JAL;
    instr->base.free_function = jal_instruction_free;
    instr->reg = reg;

    return instr;
}

void free_instruction(struct Instruction* instr)
{
    if (instr->free_function == NULL) {
        return;
    }

    instr->free_function(instr);
}