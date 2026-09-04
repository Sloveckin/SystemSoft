#include "backend/asm/riscv/asm_directive.h"

#include <malloc.h>
#include <string.h>

const char* directive_to_str[] = {
    ".global",
};

struct Directive* directive_init(const enum DirectiveType type, const char* text)
{
    struct Directive* directive = malloc(sizeof(struct Directive));
    if (directive == NULL) {
        return NULL;
    }

    const size_t text_length = strlen(text) + 1;
    directive->text = malloc(text_length * sizeof(char));
    if (directive->text == NULL) {
        free(directive);
        return NULL;
    }

    strcpy(directive->text, text);

    directive->type = type;

    return directive;
}

int write_directive(const struct Directive* directive, FILE* file)
{
    int res = fprintf(file, "%s %s\n", directive_to_str[directive->type], directive->text);
    if (res < 0) {
        return res;
    }

    return 0;
}

void directive_free(struct Directive* directive)
{
    free(directive->text);
}