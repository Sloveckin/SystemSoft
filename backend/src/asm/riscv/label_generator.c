#include "backend/asm/riscv/label_generator.h"
#include <stdio.h>

void label_generator_init(struct LabelGenerator* gen)
{
    gen->return_counter = 0;
    sprintf(gen->return_buffer, "return_%lu", gen->return_counter);
}

void label_return_update(struct LabelGenerator* gen)
{
    gen->return_counter += 1;
    sprintf(gen->return_buffer, "return_%lu", gen->return_counter);
}