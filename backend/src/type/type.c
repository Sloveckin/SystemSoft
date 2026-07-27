#include "backend/type/type.h"

const char* type_to_string[] = {
    "void",
    "int",
    "uint",
    "bool",
    "long",
    "ulong",
    "string",
};

bool types_suitable(const enum Type a, const enum Type b)
{
    if (a == b) {
        return true;
    }

    if (a == TYPE_LONG && b == TYPE_INT) {
        return true;
    }

    if (a == TYPE_ULONG && b == TYPE_ULONG) {
        return true;
    }

    return false;
}

bool type_support_arithmetic_operations(const enum Type type)
{
    return type == TYPE_INT || type == TYPE_UINT || type == TYPE_LONG || type == TYPE_ULONG;
}

bool type_support_boolean_operations(const enum Type type)
{
    return type == TYPE_BOOL;
}

bool type_is_comparable(const enum Type type)
{
    return type == TYPE_INT || type == TYPE_UINT || type == TYPE_LONG || type == TYPE_ULONG;
}