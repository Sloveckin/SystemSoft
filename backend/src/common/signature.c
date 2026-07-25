#include "backend/common/signature.h"

#include <malloc.h>
#include <assert.h>

#include "ast/ast_node_type.h"
#include "backend/common/variable.h"
#include "backend/type/type.h"
#include "colc/cstring.h"
#include "colc/map.h"
#include "colc/object_info.h"

static char* get_name(struct AstNode* node)
{
    assert(node->type == AST_TYPE_IDENTIFIER);
    const size_t name_length = strlen(node->text) + 1;
    char* name = malloc(name_length * sizeof(char));
    if (name == NULL) {
        return NULL;
    }
    strcpy(name, node->text);

    return name;
}

static enum Type get_type(struct AstNode* node)
{
    if (node->type == AST_TYPE_INT_TYPE) {
        return TYPE_INT;
    }

    assert(0);
}

static int get_argument(struct AstNode* node, struct Variable* variable)
{
    assert(node->type == AST_TYPE_ARG_DEF);
    
    struct AstNode** name_node = vector_get(&node->children, 0);
    assert(*name_node);
    char* name = get_name(*name_node);
    if (name == NULL) {
        return -1;
    }

    struct AstNode** type_node = vector_get(&node->children, 1);
    assert(*type_node);
    enum Type type = get_type(*type_node);

    variable_init(variable, name, type);

    return 0;
}

static int get_arguments(struct AstNode* node, Map* variables)
{
    assert(node->type == AST_TYPE_ARG_DEF_LIST);

    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** argument_node = vector_get(&node->children, i);
        assert(*argument_node);
        struct Variable variable;
        int err = get_argument(*argument_node, &variable);
        if (err != 0) {
            return err;
        }

        CString name;
        err = cstring_init(&name, variable.name);
        if (err != 0) {
            variable_free(&variable);
            return err;
        }

        err = map_insert(variables, &name, &variable);
        if (err != 0) {
            cstring_free(&name);
            variable_free(&variable);
            return err;
        }

        variable_free(&variable);
        cstring_free(&name);
    }

    return 0;
}

int signature_init(struct Signature* signature, struct AstNode* node)
{
    assert(node->type == AST_TYPE_FUNC_SIGNATURE);

    struct AstNode** name_node = vector_get(&node->children, 0);
    assert(*name_node);
    char* name = get_name(*name_node);

    Map variables;
    const ObjectInfo key_info = {
        .size = sizeof(CString),
        .copy = cstring_copy,
        .destructor = cstring_free,
    };
    const ObjectInfo value_info = {
        .size = sizeof(struct Variable),
        .copy = variable_copy,
        .destructor = variable_destructor,
    };

    int res = map_init_with_capacity(&variables, cstring_hash, cstring_comp, key_info, value_info, MAP_DEFAULT_CAPACITY);
    if (res != 0) {
        return res;
    }
    
    struct AstNode** arg_def_list_node = vector_get(&node->children, 1);
    if (*arg_def_list_node != NULL) {
        res = get_arguments(*arg_def_list_node,  &variables);
        if (res != 0) {
            map_free(&variables);
            return res;
        }
    }
    signature->arguments = variables;

    struct AstNode** return_type_node = vector_get(&node->children, 2);
    if (*return_type_node == NULL) {
        signature->return_type = TYPE_VOID;   
    } else {
        signature->return_type = get_type(*return_type_node);
    }
    signature->name = name;

    return 0;
}

void signature_free(struct Signature* signature)
{
    map_free(&signature->arguments);
    free(signature->name);
}