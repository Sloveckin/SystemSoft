#include "middleend/optree.h"
#include "ast/ast_node_type.h"
#include "colc/object_info.h"
#include "colc/vector.h"

#include <malloc.h>
#include <string.h>
#include <assert.h>

struct OperationTreeNode* operation_tree_create(struct AstNode* node);

int operation_tree_node_init(struct OperationTreeNode* node, const enum OperationNodeType type)
{
    node->type = type;
    node->argument = NULL;

    node->value.id = 0;
    node->value.flag = false;
    
    const ObjectInfo info = {
        .size = sizeof(struct OperationTreeNode*),
        .copy = NULL,
        .destructor = operation_tree_des, 
    };

    int err = vector_init(&node->children, info);
    if (err != 0) {
        return err;
    }
    
    return 0;
}

int operation_tree_node_init_with_argument(struct OperationTreeNode* node, const enum OperationNodeType type, const char* argument_text)
{
    int err = operation_tree_node_init(node, type);
    if (err != 0) {
        return err;
    }
    const size_t argument_text_length = strlen(argument_text) + 1;
    node->argument = malloc(argument_text_length * sizeof(char));
    if (node->argument == NULL) {
        return -1;
    }
    strcpy(node->argument, argument_text);

    return 0;
}

void operation_tree_free(struct OperationTreeNode* node)
{
    if (node->argument != NULL) {
        free(node->argument);
    }
    vector_free(&node->children);
}

void operation_tree_des(void* value)
{
    struct OperationTreeNode** node = value;
    operation_tree_free(*node);
    
    free(*node);
}


static struct OperationTreeNode* variables_creation(struct AstNode* node)
{
    assert(node->children.size == 2);
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* variables_node = *pointer;

    pointer = vector_get(&node->children, 1);
    struct AstNode* type_node = *pointer;

    struct OperationTreeNode* variables = operation_tree_create(variables_node);
    if (variables == NULL) {
        return NULL;
    }

    struct OperationTreeNode* type = operation_tree_create(type_node);
    if (type == NULL) {
        operation_tree_free(variables);
        free(variables);
        return NULL;
    }

    struct OperationTreeNode* op_tree = malloc(sizeof(struct OperationTreeNode));
    if (op_tree == NULL) {
        operation_tree_free(type);
        free(type);
        operation_tree_free(variables);
        free(variables);
        return NULL;
    }

    int err = operation_tree_node_init(op_tree, OP_NODE_CREATION_VARIABLE);
    if (err != 0) {
        operation_tree_free(op_tree);
        free(op_tree);
        operation_tree_free(type);
        free(type);
        operation_tree_free(variables);
        free(variables);
        return NULL;
    }

    err = vector_push(&op_tree->children, &variables);
    if (err != 0) {
        operation_tree_free(op_tree);
        free(op_tree);
        operation_tree_free(type);
        free(type);
        operation_tree_free(variables);
        free(variables);
        return NULL;
    }

    err = vector_push(&op_tree->children, &type);
    if (err != 0) {
        operation_tree_free(op_tree);
        free(op_tree);
        operation_tree_free(type);
        free(type);
        operation_tree_free(variables);
        free(variables);
        return NULL;
    }

    return op_tree;
}

static struct OperationTreeNode* type(struct AstNode* node)
{
    struct OperationTreeNode* op_node = malloc(sizeof(struct OperationTreeNode));
    if (op_node == NULL) {
        return NULL;
    }

    enum OperationNodeType op_type;
    if (node->type == AST_TYPE_INT_TYPE) {
        op_type = OP_NODE_TYPE_INT;
    } else if (node->type == AST_TYPE_UINT_TYPE) {
        op_type = OP_NODE_TYPE_UINT;
    } else if (node->type == AST_TYPE_LONG_TYPE) {
        op_type = OP_NODE_TYPE_LONG;
    } else if (node->type == AST_TYPE_ULONG_TYPE) {
        op_type = OP_NODE_TYPE_ULONG;
    } else if (node->type == AST_TYPE_BOOL_TYPE) {
        op_type = OP_NODE_TYPE_BOOL;
    } else if (node->type == AST_TYPE_STRING_TYPE) {
        op_type = OP_NODE_TYPE_STRING;
    } else if (node->type == AST_TYPE_ARRAY) {
        op_type = OP_NODE_TYPE_ARRAY;
    } else if (node->type == AST_TYPE_SHORT_TYPE) {
        op_type = OP_NODE_TYPE_SHORT;
    } else if (node->type == AST_TYPE_USHORT_TYPE) {
        op_type = OP_NODE_TYPE_USHORT;
    }  else {
        assert(0);
    }

    int err = operation_tree_node_init(op_node, op_type);
    if (err != 0) {
        free(op_node);
        return NULL;
    }

    if (op_type == OP_NODE_TYPE_ARRAY) {
        struct AstNode** pointer = vector_get(&node->children, 0);
        struct AstNode* node_type = *pointer;

        pointer = vector_get(&node->children, 1);
        struct AstNode* length_node = *pointer;

        struct OperationTreeNode* array_type = type(node_type);
        if (array_type == NULL) {
            operation_tree_free(op_node);
            free(op_node);
            return NULL;
        }

        struct OperationTreeNode* array_length = operation_tree_create(length_node);
        if (array_length == NULL) {
            operation_tree_free(array_type);
            free(array_type);
            operation_tree_free(op_node);
            free(op_node);
            return NULL;
        }

        err = vector_push(&op_node->children, &array_type);
        if (err != 0) {
            operation_tree_free(array_type);
            free(array_type);
            operation_tree_free(op_node);
            free(op_node);
            return NULL;
        }

        err = vector_push(&op_node->children, &array_length);
        if (err != 0) {
            operation_tree_free(array_type);
            free(array_type);
            operation_tree_free(op_node);
            free(op_node);
            return NULL;
        }

    }

    return op_node;
}

struct OperationTreeNode* list(struct AstNode* node, const enum OperationNodeType type)
{
    struct OperationTreeNode* op_node = malloc(sizeof(struct OperationTreeNode));
    if (op_node == NULL) {
        return NULL;
    }
    int err = operation_tree_node_init(op_node, type);
    if (err != 0) {
        free(op_node);
        return NULL;
    }

    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** pointer = vector_get(&node->children, i);
        struct AstNode* child = *pointer;
        struct OperationTreeNode* identifier = operation_tree_create(child);
        err = vector_push(&op_node->children, &identifier);
        if (err != 0) {
            operation_tree_free(op_node);
            free(op_node);
            return NULL;
        }
    }

    return op_node;
}

static struct OperationTreeNode* identifier_list(struct AstNode* node)
{
    return list(node, OP_NODE_IDENTIFIER_LIST);
}

struct OperationTreeNode* expr_list(struct AstNode* node)
{
    return list(node, OP_NODE_EXPR_LIST);
}

static struct OperationTreeNode* create_store(struct AstNode* node)
{
    struct OperationTreeNode* store = malloc(sizeof(struct OperationTreeNode));
    if (store == NULL) {
        return NULL;
    }

    if (node->type == AST_TYPE_IDENTIFIER) {
        int err = operation_tree_node_init_with_argument(store, OP_NODE_STORE, node->text);
        if (err != 0) {
            free(store);
            return NULL;
        }
    } else if (node->type == AST_TYPE_CALL_OR_INDEXER) {
        struct AstNode** pointer = vector_get(&node->children, 0);
        struct AstNode* name_node = *pointer;

        pointer = vector_get(&node->children, 1);
        struct AstNode* length_node = *pointer;


        struct OperationTreeNode* name = operation_tree_create(name_node);
        if (name == NULL) {
            operation_tree_free(store);
            free(store);
            return NULL;
        }

        struct OperationTreeNode* length = operation_tree_create(length_node);
        if (length == NULL) {
            operation_tree_free(name);
            free(name);
            operation_tree_free(store);
            free(store);
            return NULL;
        }

        int err = operation_tree_node_init(store, OP_NODE_STORE_ARRAY);
        if (err != 0) {
            operation_tree_free(length);
            free(length);
            operation_tree_free(name);
            free(name);
            operation_tree_free(store);
            free(store);
            return NULL;
        }

        err = vector_push(&store->children, &name);
        if (err != 0) {
            operation_tree_free(length);
            free(length);
            operation_tree_free(name);
            free(name);
            operation_tree_free(store);
            free(store);
            return NULL;
        }

        err = vector_push(&store->children, &length);
        if (err != 0) {
            operation_tree_free(length);
            free(length);
            operation_tree_free(name);
            free(name);
            operation_tree_free(store);
            free(store);
            return NULL;
        }

    }


    return store;
}

static struct OperationTreeNode* create_load(struct AstNode* node)
{
    struct OperationTreeNode* load = malloc(sizeof(struct OperationTreeNode));
    if (load == NULL) {
        return NULL;
    }

    enum OperationNodeType type;
    if (node->type == AST_TYPE_IDENTIFIER) {
        type = OP_NODE_LOAD;
    } else {
        type = OP_NODE_CONST;
    }

    int err = operation_tree_node_init_with_argument(load, type, node->text);
    if (err != 0) {
        free(load);
        return NULL;
    }

    return load;
}

static struct OperationTreeNode* assigment(struct AstNode* node)
{
    struct OperationTreeNode* assigment = malloc(sizeof(struct OperationTreeNode));
    if (assigment == NULL) {
        free(assigment);
    }

    int err = operation_tree_node_init(assigment, OP_NODE_ASSIGMENT);
    if (err != 0) {
        free(assigment);
        return NULL;
    }

    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* store_node = *pointer;

    pointer = vector_get(&node->children, 1);
    struct AstNode* load_node = *pointer;

    struct OperationTreeNode* store = create_store(store_node);
    if (store == NULL) {
        operation_tree_free(assigment);
        free(assigment);
        return NULL;
    }

    struct OperationTreeNode* load = operation_tree_create(load_node);
    if (load == NULL) {
        operation_tree_free(store);
        free(store);
        operation_tree_free(assigment);
        free(assigment);
        return NULL;
    }

    err = vector_push(&assigment->children, &store);
    if (err != 0) {
        operation_tree_free(load);
        free(load);
        operation_tree_free(store);
        free(store);
        operation_tree_free(assigment);
        free(assigment);
        return NULL;
    }

    err = vector_push(&assigment->children, &load);
    if (err != 0) {
        operation_tree_free(load);
        free(load);
        operation_tree_free(store);
        free(store);
        operation_tree_free(assigment);
        free(assigment);
        return NULL;
    }

    return assigment;
}

static struct OperationTreeNode* binary_operation(struct AstNode* node, const enum OperationNodeType type)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* left_node = *pointer;

    pointer = vector_get(&node->children, 1);
    struct AstNode* right_node = *pointer;

    struct OperationTreeNode* left = operation_tree_create(left_node);
    if (left == NULL) {
        return NULL;
    }

    struct OperationTreeNode* right = operation_tree_create(right_node);
    if (right == NULL)
    {
        operation_tree_free(left);
        free(left);
        return NULL;
    }

    struct OperationTreeNode* binary = malloc(sizeof(struct OperationTreeNode));
    if (binary == NULL) {
        operation_tree_free(right);
        free(right);
        operation_tree_free(left);
        free(left);
        return NULL;
    }

    int err = operation_tree_node_init(binary, type);
    if (err != 0) {
        operation_tree_free(binary);
        free(binary);
        operation_tree_free(right);
        free(right);
        operation_tree_free(left);
        free(left);
        return NULL;
    }

    err = vector_push(&binary->children, &left);
    if (err != 0) {
        operation_tree_free(binary);
        free(binary);
        operation_tree_free(right);
        free(right);
        operation_tree_free(left);
        free(left);
        return NULL;
    }

    err = vector_push(&binary->children, &right);
    if (err != 0) {
        operation_tree_free(binary);
        free(binary);
        operation_tree_free(right);
        free(right);
        operation_tree_free(left);
        free(left);
        return NULL;
    }

    return binary;
}

static struct OperationTreeNode* break_(struct AstNode* node)
{
    struct OperationTreeNode* op_node = malloc(sizeof(struct OperationTreeNode));
    if (op_node == NULL) {
        return NULL;
    }

    int err = operation_tree_node_init(op_node, OP_NODE_BREAK);
    if (err != 0) {
        free(op_node);
        return NULL;
    }

    return op_node;
}

static struct OperationTreeNode* return_(struct AstNode* node)
{
    struct OperationTreeNode* op_node = malloc(sizeof(struct OperationTreeNode));
    if (op_node == NULL) {
        return NULL;
    }

    int err = operation_tree_node_init(op_node, OP_NODE_RETURN);
    if (err != 0) {
        free(op_node);
        return NULL;
    }

    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* expr_node = *pointer;

    struct OperationTreeNode* expr = operation_tree_create(expr_node);
    if (expr == NULL) {
        operation_tree_free(op_node);
        free(op_node);
        return NULL;
    }

    err = vector_push(&op_node->children, &expr);
    if (err != 0) {
        operation_tree_free(expr);
        free(expr);
        operation_tree_free(op_node);
        free(op_node);
        return NULL;
    }

    return op_node;
}

static struct OperationTreeNode* call_or_indexer(struct AstNode* node)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* name_node = *pointer;

    pointer = vector_get(&node->children, 1);
    struct AstNode* expr_list_node = *pointer;

    struct OperationTreeNode* call = malloc(sizeof(struct OperationTreeNode));
    if (call == NULL) {
        return NULL;
    }

    int err = operation_tree_node_init(call,OP_NODE_CALL_OR_INDEXER);
    if (err != 0) {
        free(call);
        return NULL;
    }

    struct OperationTreeNode* name = operation_tree_create(name_node);
    if (name == NULL) {
        operation_tree_free(call);
        free(call);
        return NULL;
    }

    struct OperationTreeNode* expr_list = operation_tree_create(expr_list_node);
    if (expr_list == NULL) {
        operation_tree_free(expr_list);
        free(expr_list);
        operation_tree_free(call);
        free(call);
        return NULL;
    }

    err = vector_push(&call->children, &name);
    if (err != 0) {
        operation_tree_free(expr_list);
        free(expr_list);
        operation_tree_free(call);
        free(call);
        return NULL;
    }

    err = vector_push(&call->children, &expr_list);
    if (err != 0) {
        operation_tree_free(expr_list);
        free(expr_list);
        operation_tree_free(call);
        free(call);
        return NULL;
    }

    return call;
}

static struct OperationTreeNode* unary(struct AstNode* node, const enum OperationNodeType type)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* expr_node = *pointer;

    struct OperationTreeNode* op = malloc(sizeof(struct OperationTreeNode));
    if (op == NULL) {
        return NULL;
    }

    int err = operation_tree_node_init(op, type);
    if (err != 0) {
        free(op);
        return NULL;
    }

    
    struct OperationTreeNode* expr = operation_tree_create(expr_node);
    if (expr == NULL) {
        operation_tree_free(op);
        free(op);
        return NULL;
    }

    err = vector_push(&op->children, &expr);
    if (err != 0) {
        operation_tree_free(expr);
        free(expr);
        operation_tree_free(op);
        free(op);
        return NULL;
    }

    return op;
}

static struct OperationTreeNode* bool_(struct AstNode* node)
{
    struct OperationTreeNode* boolean = malloc(sizeof(struct OperationTreeNode));
    if (boolean == NULL) {
        return NULL;
    }

    int err;
    if (strcmp(node->text, "true") == 0) {
        err = operation_tree_node_init_with_argument(boolean, OP_NODE_TYPE_BOOL, "true");
    } else {
        err = operation_tree_node_init_with_argument(boolean, OP_NODE_TYPE_BOOL, "false");
    }

    if (err != 0) {
        free(boolean);
    }

    return boolean;
}

struct OperationTreeNode* operation_tree_create(struct AstNode* node)
{
    if (node->type == AST_TYPE_VAR) {
        return variables_creation(node); 
    } else if (node->type == AST_TYPE_IDENTIFIER_LIST) {
        return identifier_list(node);
    } else if (node->type == AST_TYPE_SHORT_TYPE
            || node->type == AST_TYPE_USHORT_TYPE
            || node->type == AST_TYPE_INT_TYPE
            || node->type == AST_TYPE_UINT_TYPE
            || node->type == AST_TYPE_LONG_TYPE
            || node->type == AST_TYPE_ULONG_TYPE
            || node->type == AST_TYPE_BOOL_TYPE
            || node->type == AST_TYPE_STRING_TYPE
            || node->type == AST_TYPE_ARRAY) {
        return type(node);
    } else if (node->type == AST_TYPE_IDENTIFIER || node->type == AST_TYPE_DEC || node->type == AST_TYPE_STR || node->type == AST_TYPE_BOOL) {
        return create_load(node);
    } else if (node->type == AST_TYPE_ASSIGMENT) {
        return assigment(node);
    } else if (node->type == AST_TYPE_PLUS) {
        return binary_operation(node, OP_NODE_PLUS);
    } else if (node->type == AST_TYPE_MINUS) {
        return binary_operation(node, OP_NODE_MINUS);
    } else if (node->type == AST_TYPE_MUL) {
        return binary_operation(node, OP_NODE_MUL);
    } else if (node->type == AST_TYPE_DIV) {
        return binary_operation(node, OP_NODE_DIV);
    } else if (node->type == AST_TYPE_OR) {
        return binary_operation(node, OP_NODE_OR);
    } else if (node->type == AST_TYPE_AND) {
        return binary_operation(node, OP_NODE_AND);
    } else if (node->type == AST_TYPE_BREAK) {
        return break_(node);
    } else if (node->type == AST_TYPE_RETURN) {
        return return_(node);
    } else if (node->type == AST_TYPE_CALL_OR_INDEXER) {
        return call_or_indexer(node);
    } else if (node->type == AST_TYPE_EXPR_LIST) {
        return expr_list(node);
    } else if (node->type == AST_TYPE_UNARY_MINUS) {
        return unary(node, OP_NODE_UNARY_MINUS);
    } else if (node->type == AST_TYPE_UNARY_PLUS) {
        return unary(node, OP_NODE_UNARY_PLUS);
    }

    // Not expected branch
    assert(0);
}