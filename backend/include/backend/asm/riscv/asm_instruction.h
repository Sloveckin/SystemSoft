#ifndef RISC_V_INSTRUCTION_H
#define RISC_V_INSTRUCTION_H

#include "backend/asm/riscv/register.h"

#include <stdio.h>

enum Mnemonic {
    MN_ADDI = 0,
    MN_SB = 1,
    MN_SH = 2,
    MN_SW = 3,
    MN_SD = 4,
    MN_LD = 5,
    MN_JAL = 6,
    MN_JALR = 7,
    MN_LB = 8,
    MN_LH = 9,
    MN_LW = 10,
    MN_ADD = 11,
    MN_CALL = 12,
    MN_SUB = 13,
};

enum InstructionFormat {
    INSTRUCTION_FORMAT_I,
    INSTRUCTION_FORMAT_S,
    INSTCURTION_FORMAT_JAL,
    INSTRUCTION_FORMAT_CALL,
    INSTRUCTION_FORMAT_R3,
};

struct Instruction {
    enum InstructionFormat format; 
    enum Mnemonic mnemonic;
    void (*free_function)(struct Instruction* instr);
};

struct ITypeInstruction {
    struct Instruction base;

    enum RegisterType r1;
    enum RegisterType r2;
    int64_t imm;
};

struct SLTypeInstruction {
    struct Instruction base;

    enum RegisterType r1;
    enum RegisterType r2;
    int64_t offset;
};

struct JalInstruction {
    struct Instruction base;

    enum RegisterType reg;
    char *label;
};

struct R3Instruction {
    struct Instruction base;
    
    enum RegisterType reg1;
    enum RegisterType reg2;
    enum RegisterType reg3;
};

struct Call {
    struct Instruction base;

    char* function_name;
};

extern const char* mnemonic_to_str[];

struct ITypeInstruction* itype_instruction_init(const enum Mnemonic mnemonic, const enum RegisterType r1, const enum RegisterType r2, const int64_t imm);

struct SLTypeInstruction* sltype_instruction_init(const enum Mnemonic mnemonic, const enum RegisterType r1, const enum RegisterType r2, const int64_t offset);

struct JalInstruction* jal_instructoin_init(const enum RegisterType reg, const char* text);

struct R3Instruction* r3_instruction_init(const enum Mnemonic, const enum RegisterType r1, const enum RegisterType r2, const enum RegisterType r3);

struct Call* call_instruction_init(const char* name);

void free_instruction(struct Instruction* instr);

int write_inscruction(struct Instruction* instruction, FILE* file);

#endif