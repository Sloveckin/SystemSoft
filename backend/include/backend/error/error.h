#ifndef BACKEND_ERROR_H
#define BACKEND_ERROR_H

#define MAX_LENGTH_ERROR_MESSAGE 1024

enum ErrorType {
    ERROR_TYPE_NOT_LVALUE,
    ERROR_VARIABLE_ALREADY_EXISTS,
};

struct Error {
    enum ErrorType type;
    char* text;
};

int error_init(struct Error* error, const enum ErrorType type, const char* text);

char* error_to_str(struct Error* error);

void error_free(struct Error* error);

int error_copy(void* dst, const void* src);

void error_desctructor(void* value);

#endif
