#include "backend/error/error.h"

#include <malloc.h>
#include <string.h>

int error_init(struct Error* error, const enum ErrorType type, const char* text)
{
    error->type = type;
    const size_t text_len = strlen(text) + 1;
    error->text = malloc(text_len * sizeof(char));
    if (error->text == NULL) {
        return -1;
    }
    strcpy(error->text, text);

    return 0;
}

char* error_to_str(struct Error* error)
{
    static char error_message[MAX_LENGTH_ERROR_MESSAGE];
    if (error->type == ERROR_TYPE_NOT_LVALUE) {
        sprintf(error_message, "Expression %s not LVALUE", error->text);
    } else if (error->type == ERROR_VARIABLE_ALREADY_EXISTS) {
        sprintf(error_message, "Variable %s already exists", error->text);
    }

    return error_message;
}   

int error_copy(void* dst, const void* src)
{
    struct Error* error_dst = dst;
    const struct Error* error_src = src;

    const size_t text_len = strlen(error_src->text) + 1;
    error_dst->text = malloc(text_len * sizeof(char));
    if (error_dst->text == NULL) {
        return -1;
    }
    strcpy(error_dst->text, error_src->text);

    error_dst->type = error_src->type;

    return 0;
}

void error_free(struct Error* error)
{
    free(error->text);
}

void error_desctructor(void* value)
{
    struct Error* error = value;
    error_free(error);
}