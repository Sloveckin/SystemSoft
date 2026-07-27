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
        if ((*value)->text == NULL) {
            vector_free(&(*value)->children);
            free(*value);
        } else {
            free((*value)->text);
            free(*value);
        }
    }
}

void ast_node_init(struct AstNode* node, const enum AstNodeType type)
{
    node->type = type;
    node->text = NULL;
    node->id = 0;

    const ObjectInfo obj_info = {
        .size = sizeof(struct AstNode*),
        .destructor = ast_node_destructor,
        .copy = NULL,
    };
    vector_init(&node->children, obj_info);
} 

int ast_node_init_with_text(struct AstNode* node, const enum AstNodeType type, const char* text)
{
    node->type = type;
    node->id = 0;
    node->text = malloc((strlen(text) + 1) * sizeof(char));
    if (node->text == NULL) {
        return -1;
    }
    strcpy(node->text, text);

    const ObjectInfo obj_info = {
        .size = sizeof(struct AstNode*),
        .destructor = ast_node_destructor,
        .copy = NULL,
    };
    vector_init(&node->children, obj_info);
    
    return 0;
}