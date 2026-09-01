#ifndef BACKEND_ASM_RISCV_STACK_RECORDING_H
#define BACKEND_ASM_RISCV_STACK_RECORDING_H

#include <stddef.h>

struct StackRecording {
    size_t size;
    size_t offset;
};

#endif