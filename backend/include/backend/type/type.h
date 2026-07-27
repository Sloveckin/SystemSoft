#ifndef TYPE_H
#define TYPE_H

#include <stdbool.h>

enum Type {
    TYPE_VOID = 0,
    TYPE_INT = 1,
    TYPE_UINT = 2,
    TYPE_BOOL = 3,
    TYPE_LONG = 4,
    TYPE_ULONG = 5,
    TYPE_STRING = 6,
};

extern const char* type_to_string[];

bool types_suitable(const enum Type a, const enum Type b);

bool type_support_arithmetic_operations(const enum Type type);

bool type_support_boolean_operations(const enum Type type);

bool type_is_comparable(const enum Type type);


#endif
