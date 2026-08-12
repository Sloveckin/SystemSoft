#include "language/type/type.h"

#include <malloc.h>

const char* type_to_string[] = {
    "void",
    "int",
    "uint",
    "bool",
    "long",
    "ulong",
    "string",
};

bool types_suitable(const struct Type* a, const struct Type* b)
{
    if (a->kind == b->kind) {
        return true;
    }

    if (a->kind == TYPE_KIND_LONG && b->kind == TYPE_KIND_INT) {
        return true;
    }

    if (a->kind == TYPE_KIND_ULONG && b->kind == TYPE_KIND_UINT) {
        return true;
    }

    return false;
}

bool type_support_arithmetic_operations(const struct Type* type)
{
    const enum TypeKind kind = type->kind;
    return kind == TYPE_KIND_INT || kind == TYPE_KIND_UINT || kind == TYPE_KIND_LONG || kind == TYPE_KIND_ULONG;
}

bool type_support_boolean_operations(const struct Type* type)
{
    return type->kind == TYPE_KIND_BOOL;
}

bool type_is_comparable(const struct Type* type)
{   
    const enum TypeKind kind = type->kind;
    return kind == TYPE_KIND_INT || kind == TYPE_KIND_UINT || kind == TYPE_KIND_LONG || kind == TYPE_KIND_ULONG;
}

struct Type* copy_type(const struct Type* type)
{
    struct Type* result;
    if (type->kind == TYPE_KIND_ARRAY) {
        struct ArrayType* type_array = (struct ArrayType*)type;
        struct ArrayType* tmp = malloc(sizeof(struct ArrayType));
        if (tmp == NULL) {
            return NULL;
        }

        tmp->element_type = copy_type(type_array->element_type);
        tmp->length = type_array->length;

        result = (struct Type*)tmp;
    } else {
        result = malloc(sizeof(struct Type));
        if (result == NULL) {
            return NULL;
        }
    }

    result->kind = type->kind;

    return result;
}

void type_ptr_des(void* value)
{
    struct Type** t = value;
    struct Type* type = *t;

    /*if (type->kind == TYPE_KIND_ARRAY) {
        struct ArrayType* array_type = (struct ArrayType*)type;
        type_ptr_des(&array_type->element_type);
    }*/

    free(type);
}