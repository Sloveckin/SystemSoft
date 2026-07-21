#include "ast/ast_node.h"

#include <malloc.h>
#include <linux/limits.h>


#include "ast/ast_node_type.h"
#include "colc/object_info.h"
#include "colc/vector.h"

void ast_node_destructor(void* v)
{
    struct AstNode** value = v;
    // Check because can contain NULL (example: ListStatment)
    if (*value != NULL) {
        vector_free(&(*value)->children);
        free(*value);
    }
}

void ast_node_init(struct AstNode* node, const enum AstNodeType type)
{
    node->type = type;

    const ObjectInfo obj_info = {
        .size = sizeof(struct AstNode*),
        .destructor = ast_node_destructor,
        .copy = NULL,
    };
    vector_init(&node->children, obj_info);
} 