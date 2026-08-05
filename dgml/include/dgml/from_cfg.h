#ifndef DGML_FROM_CFG_H
#define DGML_FROM_CFG_H

#include <stdio.h>

#include "middleend/cfg_node.h"

int from_ast_to_dgml(struct CfgNode* node, FILE* file);

#endif