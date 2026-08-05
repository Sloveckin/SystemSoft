#ifndef DGML_FROM_CFG_H
#define DGML_FROM_CFG_H

#include <stdio.h>

#include "middleend/cfg_node.h"

int from_cfg_to_dgml(const char* function_name, struct CfgNode* node, FILE* file);

#endif