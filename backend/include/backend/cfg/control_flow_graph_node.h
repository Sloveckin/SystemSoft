#ifndef CONTROL_GRAPH_NODE_H
#define CONTROL_GRAPH_NODE_H

#include "ast/ast_node.h"
#include "backend/optree/operation_tree_node.h"

struct CfgNode {
    char* text;
    struct CfgNode* defualt;
    struct CfgNode* condition;
    struct OperationTreeNode* opearation_tree;
};

int control_graph_node_init(struct CfgNode* node);

struct CfgNode* create_control_flow_graph(struct AstNode* ast_node);

void control_graph_free(struct CfgNode* ast_node);

#endif