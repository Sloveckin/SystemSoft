#include "middleend/cfg_node.h"
#include "colc/vector.h"
#include "middleend/optree.h"

#include <malloc.h>
#include <string.h>

int cfg_node_init(struct CfgNode* node, char* text, Vector* nodes)
{
    int err = cfg_node_init_empty(node, nodes);
    if (err != 0) {
        return err;
    }

    const size_t text_length = strlen(text) + 1;
    node->text = malloc(text_length * sizeof(char));
    if (node->text == NULL) {
        return -1;
    }
    strcpy(node->text, text);

    return 0;
}

int cfg_node_init_empty(struct CfgNode* node, Vector* nodes)
{
    node->def = NULL;
    node->condition = NULL;
    node->dgml_data.id = -1;
    node->dgml_data.visited = false;
    node->text = NULL;
    node->end = NULL;
    node->operation_node = NULL;
    node->asm_data.asm_generated = false;
    
    return vector_push(nodes, &node);
}


void cfg_node_free(struct CfgNode* node)
{
    if (node->text != NULL) {
        free(node->text);
    }

    if (node->operation_node != NULL) {
        operation_tree_des(&node->operation_node);
    }
}

void cfg_node_des(void* value)
{
    struct CfgNode** node = value;
    cfg_node_free(*node);
    
    free(*node);
}
