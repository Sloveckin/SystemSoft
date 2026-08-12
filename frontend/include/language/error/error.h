#ifndef BACKEND_ERROR_H
#define BACKEND_ERROR_H

#include "language/type/type.h"
#include <stddef.h>
#define MAX_LENGTH_ERROR_MESSAGE 512

enum ErrorType {
    ERROR_TYPE_NOT_LVALUE,
    ERROR_TYPE_NOT_RVALUE,
    ERROR_VARIABLE_ALREADY_EXISTS,
    ERROR_TYPE_VARIABLE_NOT_EXISTS,
    ERROR_TYPE_INVALID_TYPE,
    ERROR_TYPE_TYPE_NOT_SUPPORT_ARITHMETIC_OPERATIONS,
    ERROR_TYPE_TYPE_NOT_SUPPORT_BOOLEAN_OPERATIONS,
    ERROR_TYPE_TYPE_NOT_SUPPORT_ORDER,
    ERROR_TYPE_NOT_CALLABLE_OR_INDEXER,
    ERROR_TYPE_FUNCTION_NOT_EXISTS,
    ERROR_TYPE_INVALID_AMOUNT_OF_ARGUMENTS,
    ERROR_TYPE_BREAK_OUTSIDE_OF_CYCLE,
    ERROR_TYPE_NOT_UNSIGNED_NUMBER,
};

union ErrorData {
    char text[MAX_LENGTH_ERROR_MESSAGE];
    struct {
        enum TypeKind first_type;
        enum TypeKind second_type;
    } types;
    struct Type* type;
    struct {
        size_t expected;
        size_t provided;
    } argument_amount;
};

struct Error {
    enum ErrorType type;
    union ErrorData data;
};

void error_init(struct Error* error, const enum ErrorType type, const union ErrorData error_data);

char* error_to_str(struct Error* error);

#endif
