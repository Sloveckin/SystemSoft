#ifndef CFG_CONTEXT_H
#define CFG_CONTEXT_H

#include "colc/vector.h"
#include "middleend/cfg_node.h"

struct CfgContext {
    struct CfgNode* break_block;

    Vector nodes;
};

int cfg_context_init(struct CfgContext* ctx);

void cfg_context_free(struct CfgContext* ctx);

#endif