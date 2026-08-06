#include "middleend/cfg.h"

#include <malloc.h>
#include <assert.h>

#include "ast/ast_node.h"
#include "ast/ast_node_type.h"
#include "language/common/function.h"
#include "middleend/cfg_context.h"
#include "middleend/cfg_node.h"


static struct CfgNode* control_flow_graph_create_(struct AstNode* node, struct CfgContext* ctx);

static struct CfgNode* create_variable(struct AstNode* node);

static char* get_text(struct AstNode* node);

static char* get_text_from_identifier_list(struct AstNode* node)
{
    //assert(node->type == AST_TYPE_IDENTIFIER_LIST);

    size_t length_of_text = 0;
    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** pointer = vector_get(&node->children, i);
        struct AstNode *identifier_node = *pointer;

        length_of_text += strlen(identifier_node->text);
    }
    // Space and comma + place for \n
    length_of_text += (node->children.size - 1) * 2 + 1;
    char* text = malloc(length_of_text * sizeof(char));
    if (text == NULL) {
        return NULL;
    }   

    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* first_node = *pointer;

    strcpy(text, first_node->text);

    for (size_t i = 1; i < node->children.size; i++) {
        pointer = vector_get(&node->children, i);
        struct AstNode* node = *pointer;
        
        strcat(text, ", ");
        strcat(text, node->text);
    }

    return text;
}

static char* get_text_from_node(struct AstNode* node)
{
    const size_t text_length = strlen(node->text) + 1;
    char* text = malloc(text_length * sizeof(char));
    if (text == NULL) {
        return NULL;
    }
    strcpy(text, node->text);

    return text;
}

static char* get_text_from_type(struct AstNode* node)
{
    char* text;
    if (node->type == AST_TYPE_INT_TYPE) {
        text = malloc(4 * sizeof(char));
        if (text == NULL) {
            return NULL;
        }
        strcpy(text, "int");
    } else if (node->type == AST_TYPE_LONG_TYPE) {
        text = malloc(5 * sizeof(char));
        if (text == NULL) {
            return NULL;
        }
        strcpy(text, "long");
    } else if (node->type == AST_TYPE_BOOL_TYPE) {
        text = malloc(5 * sizeof(char));
        if (text == NULL) {
            return NULL;
        }
        strcpy(text, "bool");
    } else if (node->type == AST_TYPE_UINT_TYPE) {
        text = malloc(5 * sizeof(char));
        if (text == NULL) {
            return NULL;
        }
        strcpy(text, "uint");
    } else if (node->type == AST_TYPE_ULONG_TYPE) {
        text = malloc(6 * sizeof(char));
        if (text == NULL) {
            return NULL;
        }
        strcpy(text, "ulong");
    } else {
        assert(0);
    }

    return text;
}

static char* get_text_from_binary(struct AstNode* node, const char* sign_text)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* left_node = *pointer;

    char* left_text = get_text(left_node);
    if (left_text == NULL) {
        return NULL;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* right_node = *pointer;

    char* right_text = get_text(right_node);
    if (right_node == NULL) {
        free(left_text);
        return NULL;
    }

    const size_t left_length = strlen(left_text);
    const size_t right_length = strlen(right_text);
    const size_t sign_length = strlen(sign_text);

    char* text = malloc((left_length + right_length + sign_length + 5) * sizeof(char));
    if (text == NULL) {
        free(left_text);
        free(right_text);
        return NULL;
    }
    sprintf(text, "(%s %s %s)", left_text, sign_text, right_text);
    free(left_text);
    free(right_text);

    return text;
}

static char* get_text_from_call_or_indexer(struct AstNode* node)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* identifier_node = *pointer;

    char* identifier_text = get_text(identifier_node);
    if (identifier_node == NULL) {
        return NULL;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* arguments_node = *pointer;

    char* arguments_text = get_text(arguments_node);
    if (arguments_text == NULL) {
        free(identifier_text);
        return NULL;
    }

    const size_t left_text_length = strlen(identifier_text);
    const size_t right_text_length = strlen(arguments_text);

    char* text = malloc((left_text_length + right_text_length + 3) * sizeof(char));
    if (text == NULL) {
        free(identifier_text);
        free(arguments_text);
        return NULL;
    }

    sprintf(text, "%s(%s)", identifier_text, arguments_text);
    free(identifier_text);
    free(arguments_text);

    return text;
}


static char* get_text(struct AstNode* node)
{
    if (node->type == AST_TYPE_IDENTIFIER_LIST
    ||  node->type == AST_TYPE_EXPR_LIST) {
        return get_text_from_identifier_list(node);
    } else if (node->type == AST_TYPE_INT_TYPE
            || node->type == AST_TYPE_BOOL_TYPE
            || node->type == AST_TYPE_LONG_TYPE
            || node->type == AST_TYPE_UINT_TYPE
            || node->type == AST_TYPE_ULONG_TYPE) {
        return get_text_from_type(node);
    } else if (node->type == AST_TYPE_IDENTIFIER
            || node->type == AST_TYPE_DEC
            || node->type == AST_TYPE_BOOL) {
        return get_text_from_node(node);
    } else if (node->type == AST_TYPE_PLUS) {
        return get_text_from_binary(node, "+");
    } else if (node->type == AST_TYPE_MINUS) {
        return get_text_from_binary(node, "-");
    } else if (node->type == AST_TYPE_MUL) {
        return get_text_from_binary(node, "*");
    } else if (node->type == AST_TYPE_DIV) {
        return get_text_from_binary(node, "/");
    } else if (node->type == AST_TYPE_OR) {
        return get_text_from_binary(node, "or");
    } else if (node->type == AST_TYPE_AND) {
        return get_text_from_binary(node, "and");
    } else if (node->type == AST_TYPE_LESS) {
        return get_text_from_binary(node, "<");
    } else if (node->type == AST_TYPE_MORE) {
        return get_text_from_binary(node, ">");
    } else if (node->type == AST_TYPE_EQ) {
        return get_text_from_binary(node, "==");
    } else if (node->type == AST_TYPE_NOT_EQ) {
        return get_text_from_binary(node, "<>");
    } else if (node->type == AST_TYPE_CALL_OR_INDEXER) {
        return get_text_from_call_or_indexer(node);
    }

    assert(0);
}

static struct CfgNode* statement_list(struct AstNode* node, struct CfgContext* ctx) 
{
    if (node->children.size == 0) {
        return NULL;
    }

    struct AstNode** pointer = vector_get(&node->children, 0);
    struct CfgNode* previous = control_flow_graph_create_(*pointer, ctx);
    struct CfgNode* start = previous;

    for (size_t i = 1; i < node->children.size; i++) {
        pointer = vector_get(&node->children, i);
        struct CfgNode* statment = control_flow_graph_create_(*pointer, ctx);
        previous->def = statment;
        previous = statment;
    }

    return start;
}

static struct CfgNode* variables_creation(struct AstNode* node, struct CfgContext* ctx)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* list = *pointer;

    pointer = vector_get(&node->children, 1);
    struct AstNode* type = *pointer;

    char* list_text = get_text(list);
    if (list_text == NULL) {
        return NULL;
    }

    char* type_text = get_text(type);
    if (type_text == NULL) {
        free(list_text);
        return NULL;
    }

    const size_t list_text_length = strlen(list_text);
    const size_t type_text_length = strlen(type_text);

    char* text = malloc((list_text_length + type_text_length + 5) * sizeof(char));
    if (text == NULL) {
        free(list_text);
        free(type_text);
        return NULL;
    }

    sprintf(text, "%s as %s", list_text, type_text);
    free(list_text);
    free(type_text);

    struct CfgNode* cfg_node = malloc(sizeof(struct CfgNode));
    if (cfg_node == NULL) {
        free(text);
        return NULL;
    }
    
    int err = cfg_node_init(cfg_node, text, &ctx->nodes);
    if (err != 0) {
        free(text);
        free(cfg_node);
    }

    free(text);

    return cfg_node;
}

static struct CfgNode* assigment(struct AstNode* node, struct CfgContext* ctx)
{
    assert(node->children.size == 2);

    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* left = *pointer;

    pointer = vector_get(&node->children, 1);
    struct AstNode* right = *pointer;

    char* left_text = get_text(left);
    if (left_text == NULL) {
        return NULL;
    }

    char* right_text = get_text(right);
    if (right_text == NULL) {
        free(left_text);
        return NULL;
    }
    
    const size_t left_text_len = strlen(left_text);
    const size_t right_text_len = strlen(right_text);

    char* assigment_text = malloc((left_text_len + right_text_len + 4) * sizeof(char));
    if (assigment_text == NULL) {
        free(left_text);
        free(right_text);
        return NULL;
    }
    
    sprintf(assigment_text, "%s = %s", left_text, right_text);
    free(left_text);
    free(right_text);

    struct CfgNode* cfg_node = malloc(sizeof(struct CfgNode));
    if (cfg_node == NULL) {
        free(assigment_text);
        return NULL;
    }

    int err = cfg_node_init(cfg_node, assigment_text, &ctx->nodes);
    if (err != 0) {
        free(cfg_node);
        free(assigment_text);
        return NULL;
    }
    
    free(assigment_text);
    return cfg_node;
}

static struct CfgNode* if_block(struct AstNode* node, struct CfgContext* ctx)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* condition_node = *pointer;

    pointer = vector_get(&node->children, 1);
    struct AstNode* body_node = *pointer;

    pointer = vector_get(&node->children, 2);
    struct AstNode* else_node = *pointer;

    struct CfgNode* end = malloc(sizeof(struct CfgNode));
    if (end == NULL) {
        return NULL;
    }
    int err = cfg_node_init_empty(end, &ctx->nodes);
    if (err != 0) {
        free(end);
        return NULL;
    }

    struct CfgNode* condition = control_flow_graph_create_(condition_node, ctx);
    if (condition == NULL) {
        free(end);
        return NULL;
    }

    struct CfgNode* body = control_flow_graph_create_(body_node, ctx);
    if (body == NULL) {
        free(end);
        return NULL;
    }

    if (else_node != NULL) {
        struct CfgNode* else_block = control_flow_graph_create_(else_node, ctx);
        if (else_block == NULL) {
            free(end);
            return NULL;
        }

        condition->condition = body;
        condition->def = else_block;

        body->def = end;
        else_block->def = end;
    } else {
        condition->condition = body;
        condition->def = end;
        body->def = end;
    }

    return condition;
}

static struct CfgNode* boolean(struct AstNode* node, struct CfgContext* ctx)
{
    struct CfgNode* cfg_node = malloc(sizeof(struct CfgNode));
    if (cfg_node == NULL) {
        return NULL;
    }

    int err = cfg_node_init(cfg_node, node->text, &ctx->nodes);
    if (err != 0) {
        free(cfg_node);
        return NULL;
    }

    return cfg_node;
}

static struct CfgNode* else_block(struct AstNode* node, struct CfgContext* ctx)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* block = *pointer;

    return control_flow_graph_create_(block, ctx);
}

static struct CfgNode* control_flow_graph_create_(struct AstNode* node, struct CfgContext* ctx)
{
    if (node == NULL) {
        return NULL;
    } else if (node->type == AST_TYPE_STATMENT_LIST) {
        return statement_list(node, ctx);
    } else if (node->type == AST_TYPE_VAR) {
        return variables_creation(node, ctx);
    } else if (node->type == AST_TYPE_ASSIGMENT) {
        return assigment(node, ctx);
    } else if (node->type == AST_TYPE_IF_BLOCK) {
        return if_block(node, ctx);
    } else if (node->type == AST_TYPE_BOOL) {
        return boolean(node, ctx);
    } else if (node->type == AST_TYPE_ELSE_BLOCK) {
        return else_block(node, ctx);
    }

    assert(0);
}

static struct CfgNode* control_flow_graph_create(struct AstNode* node, struct CfgContext* ctx)
{
   return control_flow_graph_create_(node, ctx);
}

int program_control_flow_graph(struct Program* program)
{
    for (size_t i = 0; i < program->functions_ptr.capacity; i++) {
        if (program->functions_ptr.buffer[i].key == NULL) {
            continue;
        }

        struct Function** pointer = program->functions_ptr.buffer[i].value;
        struct Function* function = *pointer;
        
        struct AstNode** pointer_to_statements = vector_get(&function->ast->children, 1);

        function->cfg = control_flow_graph_create(*pointer_to_statements, &function->cfg_context);
        if (function->cfg == NULL) {
            return -1;
        }
    }

    return 0;
}