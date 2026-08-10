#include "middleend/cfg.h"

#include <malloc.h>
#include <assert.h>

#include "ast/ast_node.h"
#include "ast/ast_node_type.h"
#include "colc/cstring.h"
#include "colc/object_info.h"
#include "colc/vector.h"
#include "language/common/function.h"
#include "middleend/cfg_context.h"
#include "middleend/cfg_node.h"
#include "middleend/optree.h"


static struct CfgNode* control_flow_graph_create(struct AstNode* node, struct CfgContext* ctx);

static struct CfgNode* create_variable(struct AstNode* node);

static char* get_text(struct AstNode* node);

static char* get_text_from_identifier_list(struct AstNode* node)
{
    Vector textes;
    const ObjectInfo info = {
        .size = sizeof(CString),
        .copy = cstring_copy,
        .destructor = cstring_free,
    };

    int err = vector_init(&textes, info);
    if (err != 0) {
        return NULL;
    }

    size_t length_of_text = 0;
    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** pointer = vector_get(&node->children, i);
        struct AstNode *identifier_node = *pointer;

        char* identifier_text = get_text(identifier_node);
        if (identifier_text == NULL) {
            vector_free(&textes);
            return NULL;
        }

        CString str;
        err = cstring_init(&str, identifier_text);
        if (err != 0) {
            free(identifier_text);
            vector_free(&textes);
            return NULL;
        }

        int err = vector_push(&textes, &str);
        if (err != 0) {
            free(identifier_text);
            vector_free(&textes);
            return NULL;
        }

        length_of_text += str.length;        

        cstring_free(&str);
        free(identifier_text);
    }

    length_of_text += (textes.size - 1) * 2 + 1;
    char* text = malloc(length_of_text * sizeof(char));
    if (text == NULL) {
        vector_free(&textes);
        return NULL;
    }

    struct CString* first_string = vector_get(&textes, 0);
    strcpy(text, first_string->buffer);

    for (size_t i = 1; i < textes.size; i++) {

        struct CString* string = vector_get(&textes, i);

        strcat(text, ", ");
        strcat(text, string->buffer);
    }


    vector_free(&textes);
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
    } else if (node->type == AST_TYPE_STRING_TYPE) {
        text = malloc(7 * sizeof(char));
        if (text == NULL) {
            return NULL;
        }
        strcpy(text, "string");
    } 
    else {
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
            || node->type == AST_TYPE_ULONG_TYPE
            || node->type == AST_TYPE_STRING_TYPE) {
        return get_text_from_type(node);
    } else if (node->type == AST_TYPE_IDENTIFIER
            || node->type == AST_TYPE_DEC
            || node->type == AST_TYPE_BOOL
            || node->type == AST_TYPE_STR) {
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

static struct CfgNode* find_last_cfg_node(struct CfgNode* node, struct CfgNode* except)
{

    if (node->text != NULL && strcmp(node->text, "break") == 0) {
        return node;
    }

    if (node->def == NULL && node->end == NULL) {
        return node;
    }

    if (node->def != NULL) {
        return find_last_cfg_node(node->def, except);
    }

    return node->end;
}

static void update_default(struct CfgNode* node, struct CfgNode* to)
{
    if (node->text != NULL && strcmp(node->text, "break") == 0) {
        return;
    }

    node->def = to;
}

static struct CfgNode* statement_list(struct AstNode* node, struct CfgContext* ctx) 
{
    if (node->children.size == 0) {
        return NULL;
    }

    struct AstNode** pointer = vector_get(&node->children, 0);
    struct CfgNode* previous = control_flow_graph_create(*pointer, ctx);
    struct CfgNode* start = previous;

    for (size_t i = 1; i < node->children.size; i++) {
        pointer = vector_get(&node->children, i);
        struct CfgNode* statment = control_flow_graph_create(*pointer, ctx);

        struct CfgNode* last = find_last_cfg_node(previous, NULL);
        update_default(last, statment);
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
        return NULL;
    }
    free(text);

    cfg_node->operation_node = operation_tree_create(node);

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

    cfg_node->operation_node = operation_tree_create(node);

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

    struct CfgNode* condition = control_flow_graph_create(condition_node, ctx);
    if (condition == NULL) {
        return NULL;
    }

    struct CfgNode* body = control_flow_graph_create(body_node, ctx);
    if (body == NULL) {
        return NULL;
    }

    if (else_node != NULL) {
        struct CfgNode* else_block = control_flow_graph_create(else_node, ctx);
        if (else_block == NULL) {
            return NULL;
        }

        condition->end = end;
        condition->condition = body;
        condition->def = else_block;

        struct CfgNode* body_last = find_last_cfg_node(body, NULL);
        body_last->def = end;

        struct CfgNode* else_last = find_last_cfg_node(else_block, NULL);
        update_default(else_last, end);
    } else {
        condition->end = end;
        condition->condition = body;
        condition->def = end;

        struct CfgNode* body_last = find_last_cfg_node(body, NULL);
        update_default(body_last, end);
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

    return control_flow_graph_create(block, ctx);
}

static struct CfgNode* binary_operation(struct AstNode* node, const char* sign, struct CfgContext* ctx)
{
    char* text = get_text_from_binary(node, sign);
    struct CfgNode* cfg = malloc(sizeof(struct CfgNode));
    if (cfg == NULL) {
        free(text);
        return NULL;
    }
    
    int err = cfg_node_init(cfg, text, &ctx->nodes); 
    if (err != 0) {
        free(cfg);
        free(text);
        return NULL;
    }
    
    free(text);
    return cfg;
}

static struct CfgNode* return_(struct AstNode* node, struct CfgContext* ctx)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* expr_node = *pointer;

    char* text_expr = get_text(expr_node);
    if (text_expr == NULL) {
        return NULL;
    }

    const size_t expr_text_length = strlen(text_expr);

    char* text = malloc((expr_text_length + 10) * sizeof(char));
    if (text == NULL) {
        free(text_expr);
        return NULL;
    }
    sprintf(text, "return (%s)", text_expr);
    free(text_expr);


    struct CfgNode* cfg_node = malloc(sizeof(struct CfgNode));
    if (cfg_node == NULL) {
        free(text);
        return NULL;
    }

    int err = cfg_node_init(cfg_node, text, &ctx->nodes);
    if (err != 0) {
        free(cfg_node);
        free(text);
        return NULL;
    }
    free(text);

    return cfg_node; 
}

static struct CfgNode* while_cycle(struct AstNode* node, struct CfgContext* ctx)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* condition_node = *pointer;

    struct CfgNode* condition = control_flow_graph_create(condition_node, ctx);
    if (condition == NULL) {
        return NULL;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* statments_node = *pointer;

    struct CfgNode* end = malloc(sizeof(struct CfgNode));
    if (end == NULL) {
        return NULL;
    }
    int err = cfg_node_init_empty(end, &ctx->nodes);
    if (err != 0) {
        free(end);
        return NULL;
    }
    ctx->after_cycle = end;


    struct CfgNode* statments = control_flow_graph_create(statments_node, ctx);
    if (statments == NULL) {
        return NULL;
    }

    condition->end = end;
    condition->def = end;
    condition->condition = statments;

    struct CfgNode* last_statment = find_last_cfg_node(statments, end);
    update_default(last_statment, condition);
    return condition;
}

static struct CfgNode* do_cycle(struct AstNode* node, struct CfgContext* ctx)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* statments_node = *pointer;

    pointer = vector_get(&node->children, 1);
    struct AstNode* while_or_cycle = *pointer;

    pointer = vector_get(&node->children, 2);
    struct AstNode* condition_node = *pointer;

    struct CfgNode* end = malloc(sizeof(struct CfgNode));
    if (end == NULL) {
        return NULL;
    }
    int err = cfg_node_init_empty(end, &ctx->nodes);
    if (err != 0) {
        free(end);
    }
    ctx->after_cycle = end;

    struct CfgNode* statments = control_flow_graph_create(statments_node, ctx);
    if (statments == NULL) {
        return NULL;
    }

    struct CfgNode* condition = control_flow_graph_create(condition_node, ctx);
    if (condition == NULL) {
        return NULL;
    }


    struct CfgNode* last_statment = find_last_cfg_node(statments, end);
    update_default(last_statment, condition);

    statments->end = end;
    if (while_or_cycle->type == AST_TYPE_WHILE) {
        condition->def = end;
        condition->condition = statments;
    } else {
        assert(while_or_cycle->type == AST_TYPE_UNTIL);
        condition->condition = end;
        condition->def = statments;
    }

    ctx->after_cycle = NULL;
    return statments;
}

static struct CfgNode* break_(struct AstNode* node, struct CfgContext* ctx)
{
    struct CfgNode* cfg_node = malloc(sizeof(struct CfgNode));
    if (cfg_node == NULL) {
        return NULL;
    }

    int err = cfg_node_init(cfg_node, "break", &ctx->nodes);
    if (err != 0) {
        free(cfg_node);
        return NULL;
    }

    assert(ctx->after_cycle != NULL);
    cfg_node->def = ctx->after_cycle;

    return cfg_node;
}

static struct CfgNode* control_flow_graph_create(struct AstNode* node, struct CfgContext* ctx)
{
    if (node->type == AST_TYPE_STATMENT_LIST) {
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
    } else if (node->type == AST_TYPE_OR) {
        return binary_operation(node, "or", ctx);
    } else if (node->type == AST_TYPE_AND) {
        return binary_operation(node, "and", ctx);
    } else if (node->type == AST_TYPE_LESS) {
        return binary_operation(node, "<", ctx);
    } else if (node->type == AST_TYPE_MORE) {
        return binary_operation(node, ">", ctx);    
    } else if (node->type == AST_TYPE_EQ) {
        return binary_operation(node, "==", ctx);
    } else if (node->type == AST_TYPE_NOT_EQ) {
        return binary_operation(node, "<>", ctx);
    } else if (node->type == AST_TYPE_RETURN) {
        return return_(node, ctx);
    } else if (node->type == AST_TYPE_WHILE_CYCLE) {
        return while_cycle(node, ctx);
    } else if (node->type == AST_TYPE_DO) {
        return do_cycle(node, ctx);
    } else if (node->type == AST_TYPE_BREAK) {
        return break_(node, ctx);
    }

    assert(0);
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