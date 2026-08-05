#include "middleend/cfg.h"

#include <malloc.h>
#include <assert.h>

#include "ast/ast_node.h"
#include "ast/ast_node_type.h"
#include "language/common/function.h"
#include "middleend/cfg_node.h"


static struct CfgNode* control_flow_graph_create(struct AstNode* node);

static struct CfgNode* create_variable(struct AstNode* node);

static char* get_text_from_identifier_list(struct AstNode* node)
{
    assert(node->type == AST_TYPE_IDENTIFIER_LIST);

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

static char* get_text(struct AstNode* node)
{
    if (node->type == AST_TYPE_IDENTIFIER_LIST) {
        return get_text_from_identifier_list(node);
    } else if (node->type == AST_TYPE_INT_TYPE
            || node->type == AST_TYPE_BOOL_TYPE
            || node->type == AST_TYPE_LONG_TYPE
            || node->type == AST_TYPE_UINT_TYPE
            || node->type == AST_TYPE_ULONG_TYPE) {
        return get_text_from_type(node);
    }

    assert(0);
}

static struct CfgNode* statement_list(struct AstNode* node) 
{
    if (node->children.size == 0) {
        return NULL;
    }

    struct AstNode** pointer = vector_get(&node->children, 0);
    struct CfgNode* previous = control_flow_graph_create(*pointer);
    struct CfgNode* start = previous;

    for (size_t i = 1; i < node->children.size; i++) {
        pointer = vector_get(&node->children, i);
        struct CfgNode* statment = control_flow_graph_create(*pointer);
        previous->def = statment;
        previous = statment;
    }

    return start;
}

static struct CfgNode* variables_creation(struct AstNode* node)
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
    
    int err = cfg_node_init(cfg_node, text);
    if (err != 0) {
        free(text);
        free(cfg_node);
    }

    free(text);

    return cfg_node;
}

static struct CfgNode* control_flow_graph_create(struct AstNode* node)
{
    if (node->type == AST_TYPE_STATMENT_LIST) {
        return statement_list(node);
    } else if (node->type == AST_TYPE_VAR) {
        return variables_creation(node);
    }

    assert(0);
}

static void control_flow_graph_free(struct CfgNode* node)
{

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

        function->cfg = control_flow_graph_create(*pointer_to_statements);
        if (function->cfg == NULL) {
            return -1;
        }
        puts(function->cfg->text);
    }

    return 0;
}