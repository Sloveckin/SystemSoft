#include "middleend/optree.h"

#include <malloc.h>
#include <string.h>
#include <assert.h>

void operation_tree_node_init(struct OperationTreeNode* node, const enum OperationNodeType type)
{
    node->type = type;
    node->argument = NULL;
}

int operation_tree_node_init_with_argument(struct OperationTreeNode* node, const enum OperationNodeType type, const char* argument_text)
{
    operation_tree_node_init(node, type);
    const size_t argument_text_length = strlen(argument_text) + 1;
    node->argument = malloc(argument_text_length * sizeof(char));
    if (node->argument == NULL) {
        return -1;
    }
    strcpy(node->argument, argument_text);

    return 0;
}

static struct OperationTreeNode* variable_creation(struct AstNode* node)
{
    assert(0);
}

struct OperationTreeNode* operation_tree_create(struct AstNode* node)
{
    if (node->type == AST_TYPE_VAR) {
        return  variable_creation(node); 
    }

    // Not expected branch
    assert(0);
}