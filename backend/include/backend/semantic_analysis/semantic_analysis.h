#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include <stdbool.h>
#include <stdint.h>

#include "backend/program.h"
#include "backend/type/type.h"

struct ExpressionInfo {
    struct Type* type;
    bool is_constant;

    union {
        int64_t number;
        uint64_t unumber;
        bool boolean;
    } value;
};

int program_semantic_analysis(struct Program* program);

#endif