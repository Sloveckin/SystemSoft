#include "language/error/error.h"
#include "language/type/type.h"

#include <malloc.h>
#include <assert.h>
#include <stdio.h>

void error_init(struct Error* error, const enum ErrorType type, const union ErrorData error_data)
{
    error->type = type;
    error->data = error_data;
}

char* error_to_str(struct Error* error)
{
    static char error_message[MAX_LENGTH_ERROR_MESSAGE];
    if (error->type == ERROR_TYPE_NOT_LVALUE) {
        sprintf(error_message, "Expression %s not LVALUE", error->data.text);
    } else if (error->type == ERROR_VARIABLE_ALREADY_EXISTS) {
        sprintf(error_message, "Variable %s already exists", error->data.text);
    } else if (error->type == ERROR_TYPE_VARIABLE_NOT_EXISTS) {
        sprintf(error_message, "Variable with name %s not exists", error->data.text);
    } else if (error->type == ERROR_TYPE_INVALID_TYPE) {
        const char* first_type_str = type_to_string[error->data.types.first_type];
        const char* second_type_str = type_to_string[error->data.types.second_type];
        sprintf(error_message, "Invalid types. Expected %s, but was %s", first_type_str, second_type_str);
    } else if (error->type == ERROR_TYPE_TYPE_NOT_SUPPORT_ARITHMETIC_OPERATIONS) {
        const char* type_str = type_to_string[error->data.type->kind];
        sprintf(error_message, "Type %s not supports arithmetic operations", type_str);
    } else if (error->type == ERROR_TYPE_TYPE_NOT_SUPPORT_BOOLEAN_OPERATIONS) {
        const char* type_str = type_to_string[error->data.type->kind];
        sprintf(error_message, "Type %s not supports boolean operations", type_str);
    } else if (error->type == ERROR_TYPE_NOT_CALLABLE_OR_INDEXER) {
        sprintf(error_message, "Expression %s can't be called", error->data.text);
    } else if (error->type == ERROR_TYPE_FUNCTION_NOT_EXISTS) {
        sprintf(error_message, "Function with name = %s not exists", error->data.text);
    } else if (error->type == ERROR_TYPE_INVALID_AMOUNT_OF_ARGUMENTS) {
        sprintf(error_message, "Invalid arguments amount. Expected %zu, but was %zu", error->data.argument_amount.expected, error->data.argument_amount.provided);
    } else if (error->type == ERROR_TYPE_TYPE_NOT_SUPPORT_ORDER) {
        const char* type_str = type_to_string[error->data.type->kind];
        sprintf(error_message, "Type %s not support ordering", type_str);
    } else if (error->type == ERROR_TYPE_BREAK_OUTSIDE_OF_CYCLE) {
        sprintf(error_message, "Break outside of cycle");
    } else if (error->type == ERROR_TYPE_NOT_UNSIGNED_NUMBER) {
        sprintf(error_message, "Expression can't be converted to unsigned number");
    } else if (error->type == ERROR_TYPE_NOT_RVALUE) {
        sprintf(error_message, "Expression %s not rvalue", error->data.text);
    } else {
        assert(0);
    }

    return error_message;
}
