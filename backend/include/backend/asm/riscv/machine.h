#ifndef RISCV_MACHINE_H
#define RISCV_MACHINE_H

#include "backend/asm/riscv/register.h"

#define REGISTER_AMOUNT 32

struct RiscVMachine {
    struct Register registers[REGISTER_AMOUNT];
};

void riscv_machine_init(struct RiscVMachine* machine);

void riscv_machine_free(struct RiscVMachine* machine);

struct Register* riscv_machine_get_caller_save_reg(struct RiscVMachine* machine);

struct Register* riscv_machine_get_temp_register(struct RiscVMachine* machine);

#endif