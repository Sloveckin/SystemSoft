#ifndef PROGRAM_H
#define PROGRAM_H

#include "colc/map.h"
struct Program {
    Map signatures_ptr;
    Map functions_ptr;
};

int program_init(struct Program* program);

void program_free(struct Program* program);


#endif