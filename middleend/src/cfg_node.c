#include "middleend/cfg_node.h"

#include <malloc.h>
#include <string.h>

int cfg_node_init(struct CfgNode* node, char* text)
{
    const size_t text_length = strlen(text) + 1;
    node->text = malloc(text_length * sizeof(char));
    if (node->text == NULL) {
        return -1;
    }
    strcpy(node->text, text);

    node->def = NULL;
    node->condition = NULL;
    node->dgml_data.id = -1;
    node->dgml_data.visited = false;

    return 0;
}

void cfg_node_free(struct CfgNode* node)
{
    free(node->text);
}