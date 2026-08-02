#include "backend/common/variable.h"
#include "backend/type/type.h"

#include <malloc.h>
#include <string.h>

void variable_init(struct Variable* variable, char* name, struct Type* type)
{
    variable->name = name;
    variable->type = type;
}

void variable_free(struct Variable* variable)
{
    free(variable->name);
}

int variable_copy(void* dst, const void* src)
{
    struct Variable* variable_dst = dst;
    const struct Variable* variable_src = src;

    //variable_dst->type = copy_type(variable_src->type);

    variable_dst->type = variable_src->type;

    const size_t name_len = strlen(variable_src->name) + 1;
    variable_dst->name = malloc(name_len * sizeof(char));
    if (variable_dst->name == NULL) {
        return -1;
    }
    strcpy(variable_dst->name, variable_src->name);
    return 0;
}

void variable_destructor(void* variable)
{
    struct Variable* var = variable;
    variable_free(var);
}
