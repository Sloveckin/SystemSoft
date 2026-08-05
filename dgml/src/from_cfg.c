#include "dgml/from_cfg.h"
#include "middleend/cfg_node.h"

void init_control_graph_id_(struct CfgNode *node, int* dgml_id)
{
  if (!node)
    return;

  if (node->dgml_data.visited == true)
    return;

  node->dgml_data.visited = true;
  
  node->dgml_data.id = (*dgml_id)++;
  
  init_control_graph_id_(node->def, dgml_id);
  init_control_graph_id_(node->condition, dgml_id);
}

inline static void print_start_node(const char *function_name, FILE *file)
{
  fprintf(file, "<Node Id=\"0\" Label=\"%s\" />\n", function_name);
}

inline static void print_start_link(FILE *file)
{
  fprintf(file, "<Link Source=\"0\" Target=\"1\"/>\n");
}

static void print_node(FILE *file, struct CfgNode *node)
{
  if (!node)
    return;

  if (node->dgml_data.visited == false)
    return;
  
  node->dgml_data.visited = false;

  fprintf(file, "<Node Id=\"%d\" Label=\"%s\" />\n", node->dgml_data.id, node->text);

  print_node(file, node->def);
  print_node(file, node->condition);
}

static void print_nodes(const char *function_name, FILE *file, struct CfgNode *node)
{
  fputs("<Nodes>\n", file);
  print_start_node(function_name, file);
  print_node(file, node);
  fputs("</Nodes>\n", file);
}

static void print_link(FILE *file, struct CfgNode* node)
{
  if (!node)
    return;

  if (node->dgml_data.visited == true)
    return;
  
  node->dgml_data.visited = true;

  if (node->def)
    fprintf(file, "<Link Source=\"%d\" Target=\"%d\"/>\n", node->dgml_data.id, node->def->dgml_data.id);

  if (node->condition)
    fprintf(file, "<Link Source=\"%d\" Target=\"%d\" StrokeDashArray=\"4,2\" />\n", node->dgml_data.id, node->condition->dgml_data.id);

  print_link(file, node->def);
  print_link(file, node->condition);
  
}

static void print_links(FILE *file, struct CfgNode *node)
{
  fputs("<Links>\n", file);
  print_start_link(file);
  print_link(file, node);
  fputs("</Links>\n", file);
}


int from_cfg_to_dgml(const char *function_name, struct CfgNode *node,FILE *file)
{
  int id = 1;
  init_control_graph_id_(node, &id);

  fputs("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<DirectedGraph xmlns=\"http://schemas.microsoft.com/vs/2009/dgml\" Layout=\"Sugiyama\" GraphDirection=\"TopToBottom\">\n", file);
  print_nodes(function_name, file, node);
  print_links(file, node);
  fputs("</DirectedGraph>\n", file);
  return 0;
}