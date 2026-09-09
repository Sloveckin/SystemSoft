#ifndef BACKEND_ASM_RISCV_LABEL_GENERATOR_H
#define BACKEND_ASM_RISCV_LABEL_GENERATOR_H

#include <stddef.h>

#define LABEL_LENGTH 128

struct LabelGenerator {
    size_t return_counter;
    char return_buffer[LABEL_LENGTH];
};

void label_generator_init(struct LabelGenerator* gen);

void label_return_update(struct LabelGenerator* gen);


#endif