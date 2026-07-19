#include "ast/ast_node.h"
#include "colc/object_info.h"
#include "colc/vector.h"
#include <linux/limits.h>


void ast_node_destructor(struct AstNode *v)
{
    struct AstNode* value = v;
    vector_free(&value->children);
}

void ast_node_init(struct AstNode *node, const enum AstNodeType type)
{
    node->type = type;

    const ObjectInfo obj_info = {
        .size = sizeof(struct AstNode*),
        .destructor = NULL,
        .copy = NULL,
    };
    vector_init(&node->children, obj_info);
}