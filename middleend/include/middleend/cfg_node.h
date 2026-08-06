#ifndef CFG_NODE_H
#define CFG_NODE_H

#include "colc/vector.h"
#include <stdbool.h>

struct CfgNode {
    char* text;
    struct CfgNode* def;
    struct CfgNode* condition;

    struct {
        int id;
        bool visited;
    } dgml_data;
};

int cfg_node_init(struct CfgNode* node, char* text, Vector* nodes);

int cfg_node_init_empty(struct CfgNode* node, Vector* nodes);

void cfg_node_free(struct CfgNode* node);

void cfg_node_des(void* value);


#endif