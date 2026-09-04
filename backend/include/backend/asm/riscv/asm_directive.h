#ifndef BACKEND_ASM_RISCV_ASM_DIRECTIVE_H
#define BACKEND_ASM_RISCV_ASM_DIRECTIVE_H

#include <stdio.h>
enum DirectiveType {
    GLOBAL
};

struct Directive {
    enum DirectiveType type;
    char* text;
};

extern const char* directive_to_str[];

struct Directive* directive_init(const enum DirectiveType type, const char* text);

int write_directive(const struct Directive* directive, FILE* file);

void directive_free(struct Directive* directive);

#endif