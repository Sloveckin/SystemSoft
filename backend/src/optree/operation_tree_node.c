#include "backend/optree/operation_tree_node.h"

#include <malloc.h>
#include <assert.h>

#include "ast/ast_node_type.h"
#include "colc/object_info.h"
#include "colc/vector.h"

static void operation_tree_node_descturctor(void* value)
{
    struct OperationTreeNode** node = value;
    operation_tree_node_free(*node);
}

int operation_tree_node_init(struct OperationTreeNode* node, const enum OperationTreeNodeType type)
{
    node->type = type;
    
    const ObjectInfo obj_info = {
        .size = sizeof(struct OperationTreeNode),
        .copy = NULL,
        .destructor = operation_tree_node_descturctor,
    };
    int err = vector_init(&node->data.children, obj_info);
    if (err != 0) {
        return err;
    }

    return 0;
}

int operation_tree_node_list_init(struct OperationTreeNode* node, const enum OperationTreeNodeType type, const char* argument)
{
    node->type = type;
    const size_t argument_len = strlen(argument) + 1;
    node->data.argument = malloc(argument_len * sizeof(char));
    if (node->data.argument != NULL) {
        return -1;
    }
    strcpy(node->data.argument, argument);
    return 0;
}

void operation_tree_node_free(struct OperationTreeNode* node)
{
    for (size_t i = 0; i < node->data.children.size; i++) {
        struct OperationTreeNode** pointer;
        pointer = vector_get(&node->data.children, i);
        operation_tree_node_free(*pointer);
    }
    vector_free(&node->data.children);
    free(node);
}

static struct OperationTreeNode* store(struct AstNode* ast_node)
{
    return NULL;
}

static struct OperationTreeNode* assigment(struct AstNode* ast_node)
{
    struct OperationTreeNode* node = malloc(sizeof(struct OperationTreeNode));
    if (node == NULL) {
        return NULL;
    }
    int err = operation_tree_node_init(node, OP_TREE_NODE_TYPE_ASSIGMENT);
    if (err != 0) {
        free(node);
        return NULL;
    }

    struct AstNode** pointer;
    pointer = vector_get(&ast_node->children, 0);

    struct OperationTreeNode* stre = store(*pointer);

    return node;
}

struct OperationTreeNode* opeartion_tree_create(struct AstNode* ast_node)
{
    if (ast_node->type == AST_TYPE_ASSIGMENT) {
        return assigment(ast_node);
    }

    assert(0);
}