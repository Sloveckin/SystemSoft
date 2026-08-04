#include "language/common/signature.h"

#include <malloc.h>
#include <assert.h>

#include "ast/ast_node_type.h"

#include "language/type/type.h"
#include "colc/vector.h"

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

static struct Type* init_basic_type(enum TypeKind type_kind, int *error)
{
    struct Type* type = malloc(sizeof(struct Type));
    if (type == NULL) {
        *error = -1;
        return NULL;
    }
    type->kind = type_kind;
    
    return type;
}

int signature_init(struct Signature* signature, struct AstNode* node, struct Program* program)
{
    assert(node->type == AST_TYPE_FUNC_SIGNATURE);

    struct AstNode** name_node = vector_get(&node->children, 0);
    assert(*name_node);
    char* name = get_name(*name_node);

    struct AstNode** return_type_node = vector_get(&node->children, 2);

    signature->semantic_context = malloc(sizeof(struct SemanticContext));
    if (signature->semantic_context == NULL) {
        return -1;
    }

    int err = semantic_analysis_context_init(signature->semantic_context, program);
    if (err != 0) {
        free(signature->semantic_context);
        return -1;
    }

    signature->name = name;
    signature->ast = node;

    return 0;
}

void signature_free(struct Signature* signature)
{
    vector_free(&signature->arguments);
    semantic_analysis_context_free(signature->semantic_context);
    free(signature->semantic_context);
    free(signature->name);
}

void signature_ptr_free(void* value)
{
    struct Signature** signature = value;
    signature_free(*signature);
    free(*signature);
}
