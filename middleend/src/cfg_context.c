#include "middleend/cfg_context.h"
#include "colc/object_info.h"
#include "middleend/cfg_node.h"

#include <string.h>

int cfg_context_init(struct CfgContext* ctx)
{
    ctx->break_block = NULL;

    const ObjectInfo info = {
        .size = sizeof(struct CfgNode*),
        .copy = NULL,
        .destructor = cfg_node_des,
    };

    int err = vector_init(&ctx->nodes, info);
    if (err != 0) {
        return err;
    }

    return 0;
}

void cfg_context_free(struct CfgContext* ctx)
{
    vector_free(&ctx->nodes);
}