#include "backend/asm/riscv/label_generator.h"
#include <stdio.h>

void label_generator_init(struct LabelGenerator* gen)
{
    gen->return_counter = 0;
    gen->true_block_counter = 0;
    gen->false_block_counter = 0;
    gen->after_block_counter = 0;
    sprintf(gen->return_buffer, "return_%lu", gen->return_counter);
    sprintf(gen->true_block_buffer, "true_block_%lu", gen->true_block_counter);
    sprintf(gen->false_block_buffer, "false_block_%lu", gen->false_block_counter);
    sprintf(gen->after_block_buffer, "after_block_%lu", gen->after_block_counter);
}

void label_return_update(struct LabelGenerator* gen)
{
    gen->return_counter += 1;
    sprintf(gen->return_buffer, "return_%lu", gen->return_counter);
}

void label_true_block_update(struct LabelGenerator* gen)
{
    gen->true_block_counter += 1;
    sprintf(gen->true_block_buffer, "true_block_%lu", gen->true_block_counter);
}

void label_false_block_update(struct LabelGenerator* gen)
{
    gen->false_block_counter += 1;
    sprintf(gen->false_block_buffer, "false_block_%lu", gen->false_block_counter);
}

void label_after_block_update(struct LabelGenerator* gen)
{
    gen->after_block_counter += 1;
    sprintf(gen->after_block_buffer, "after_block_%lu", gen->after_block_counter);
}