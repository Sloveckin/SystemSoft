#include "backend/cfg/control_flow_graph_node.h"


#include "ast/ast_node_type.h"
#include "backend/optree/operation_tree_node.h"

#include <malloc.h>
#include <string.h>
#include <assert.h>


int control_graph_node_init(struct CfgNode *node)
{
    node->text = NULL;
    node->defualt = NULL;
    node->condition = NULL;
    node->opearation_tree = NULL;
    return 0;
}

void control_graph_free(struct CfgNode* node)
{
    if (node->opearation_tree != NULL) {
        operation_tree_node_free(node->opearation_tree);
    }

    if (node->text != NULL) {
        free(node->text);
    }

    if (node->defualt != NULL) {
        control_graph_free(node->defualt);
    }

    if (node->condition != NULL) {
        control_graph_free(node->condition);
    }

    free(node);
}

static char* get_text_from_ast_node(struct AstNode* node)
{
    assert(node->text);
    const size_t text_len = strlen(node->text) + 1;
    char* text = malloc(text_len * sizeof(char));
    if (text == NULL) {
        return NULL;
    }
    strcpy(text, node->text);
    return text;
}

static struct CfgNode* assigment(struct AstNode* ast_node)
{
    assert(ast_node->children.size == 2);

    struct AstNode** pointer;

    pointer = vector_get(&ast_node->children, 0);
    struct AstNode* left_node = *pointer;

    pointer = vector_get(&ast_node->children, 1);
    struct AstNode* right_node = *pointer;

    char* left_text = get_text_from_ast_node(left_node);
    char* right_text = get_text_from_ast_node(right_node);

    const size_t text_len = strlen(left_text) + strlen(right_text) + 4;
    char* text = malloc(text_len * sizeof(char));
    if (text == NULL) {
        free(left_text);
        free(right_text);
        return NULL;
    }
    sprintf(text, "%s = %s", left_text, right_text);
    free(left_text);
    free(right_text);

    struct CfgNode *node = malloc(sizeof(struct CfgNode));
    if (node == NULL) {
        return NULL;
    }
    int res = control_graph_node_init(node);
    if (res != 0) {
        return NULL;
    }

    node->text = text;

    node->opearation_tree = opeartion_tree_create(ast_node);

    return node;
}

static struct CfgNode* statement(struct AstNode* ast_node) 
{
    if (ast_node->type == AST_TYPE_ASSIGMENT) {
        return assigment(ast_node);
    }

    assert(0);
}

struct CfgNode* create_control_flow_graph(struct AstNode* ast_node)
{
    assert(ast_node->type == AST_TYPE_STATMENT_LIST);
    struct CfgNode* cfg_node = malloc(sizeof(struct CfgNode));
    if (cfg_node == NULL) {
        return NULL;
    }
    int res = control_graph_node_init(cfg_node);
    if (res != 0) {
        free(cfg_node);
        return NULL;
    }

    struct CfgNode* prev = cfg_node;
    for (size_t i = 0; i < ast_node->children.size; i++) {
        struct AstNode** first_statement = vector_get(&ast_node->children, i);
        assert(*first_statement);
        struct CfgNode* next = statement(*first_statement);
        prev->defualt = next;
        prev = next;
    }

    return cfg_node;
}
