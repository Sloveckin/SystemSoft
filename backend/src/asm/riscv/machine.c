#include "backend/asm/riscv/machine.h"
#include "backend/asm/riscv/register.h"

#include <stddef.h>

void riscv_machine_init(struct RiscVMachine* machine)
{
    for (size_t i = 0; i < REGISTER_AMOUNT; i++) {
        struct Register* reg = &machine->registers[i];
        
        reg->type = i;
        reg->used = false;
        reg->offset = 0;
    }
    // Use for stack
    machine->registers[S0].used = true;
}


static struct Register* get_register(struct RiscVMachine* machine, const enum RegisterType from, const enum RegisterType to)
{
    for (size_t i = from; i <= to; i++) {
        if (machine->registers[i].used == false) {
            machine->registers[i].used = true;
            return &machine->registers[i];
        }
    }

    return NULL;
}

struct Register* riscv_machine_get_caller_save_reg(struct RiscVMachine* machine)
{
    struct Register* reg = get_register(machine, S0, S1);
    if (reg != NULL) {
        return reg;
    }

    return get_register(machine, S2, S11);
}

struct Register* riscv_machine_get_temp_register(struct RiscVMachine* machine)
{
    struct Register* reg = get_register(machine, T1, T2);
    if (reg != NULL) {
        return reg;
    }

    return get_register(machine, T3, T6);
}
