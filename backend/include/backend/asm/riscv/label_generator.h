#ifndef BACKEND_ASM_RISCV_LABEL_GENERATOR_H
#define BACKEND_ASM_RISCV_LABEL_GENERATOR_H

#include <stddef.h>

#define LABEL_LENGTH 128

struct LabelGenerator {
    size_t return_counter;
    char return_buffer[LABEL_LENGTH];

    size_t true_block_counter;
    char true_block_buffer[LABEL_LENGTH];

    size_t false_block_counter;
    char false_block_buffer[LABEL_LENGTH];

    size_t after_block_counter;
    char after_block_buffer[LABEL_LENGTH];
};

void label_generator_init(struct LabelGenerator* gen);

void label_return_update(struct LabelGenerator* gen);

void label_true_block_update(struct LabelGenerator* gen);

void label_false_block_update(struct LabelGenerator* gen);

void label_after_block_update(struct LabelGenerator* gen);



#endif