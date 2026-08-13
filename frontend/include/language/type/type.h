#ifndef TYPE_H
#define TYPE_H

#include <stdbool.h>
#include <stddef.h>

enum TypeKind {
    TYPE_KIND_VOID = 0,
    TYPE_KIND_INT = 1,
    TYPE_KIND_UINT = 2,
    TYPE_KIND_BOOL = 3,
    TYPE_KIND_LONG = 4,
    TYPE_KIND_ULONG = 5,
    TYPE_KIND_STRING = 6,
    TYPE_KIND_ARRAY = 7,
    TYPE_KIND_CHAR = 8,
};

struct Type {
    enum TypeKind kind;
};

struct ArrayType {
    struct Type base;

    size_t length;
    struct Type* element_type;
};


extern const char* type_to_string[];

bool types_suitable(const struct Type* a, const struct Type* b);

bool type_support_arithmetic_operations(const struct Type* type);

bool type_support_boolean_operations(const struct Type* type);

bool type_is_comparable(const struct Type* type);

struct Type* copy_type(const struct Type* type);

int type_copy_by_ptr(void* dst, const void* src);

void type_ptr_des(void* type);

#endif
