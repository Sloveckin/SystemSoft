#include "dgml/ast.h"

#include <linux/limits.h>
#include <assert.h>

#include "colc/vector.h"

static int print_node(struct AstNode* node, FILE* file)
{
    if (node->text != NULL) {
        fprintf(file, "<Node Id=\"%d\" Label=\"%s: %s\" />\n", node->id, ast_type_to_string[node->type], node->text);
        return 0;
    }
    
    fprintf(file, "<Node Id=\"%d\" Label=\"%s\" />\n", node->id, ast_type_to_string[node->type]);

    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** child = vector_get(&node->children, i);
        int res = print_node(*child, file);
        if (res != 0) {
            return res;
        }
    }
  
    return 0;
}

static int print_nodes(struct AstNode* node, FILE* file)
{
    int res = fputs("<Nodes>\n", file);
    if (res == EOF) {
        return res;
    }

    res = print_node(node, file);
    if (res != 0) {
        return res;
    }

    res = fputs("</Nodes>\n", file);
    if (res == EOF) {
        return res;
    }
    return 0;
}



static int print_link(struct AstNode* node, FILE* file)
{

    if (node->text != NULL) {
        return 0;
    }
    
    //fprintf(file, "<Node Id=\"%zu\" Label=\"%s\" />\n", cur_index, ast_type_to_string[node->type]);
    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** child = vector_get(&node->children, i);
        fprintf(file, "<Link Source=\"%d\" Target=\"%d\"/>\n", node->id, (*child)->id);
        print_link(*child, file);
    }
  
    return 0;
}

static int print_links(struct AstNode* node, FILE* file)
{
    int res = fputs("<Links>\n", file);
    if (res == EOF) {
        return res;
    }
    res = print_link(node, file);
    if (res != 0) {
        return res;
    }
    res = fputs("</Links>\n", file);
    if (res == EOF) {
        return res;
    }
    
    return 0;
}

static void set_nodes_id(struct AstNode* node, int* id)
{
    node->id = (*id)++;
    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** child = vector_get(&node->children, i);
        set_nodes_id(*child, id);
    }
}

int from_ast_to_dgml(struct AstNode* node, FILE* file)
{
    int id = 0;
    set_nodes_id(node, &id);
    
    int res = fputs("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<DirectedGraph xmlns=\"http://schemas.microsoft.com/vs/2009/dgml\" Layout=\"Sugiyama\" GraphDirection=\"TopToBottom\">\n", file);
    if (res == EOF) {
        return EOF;
    }
    res = print_nodes(node, file);
    if (res != 0) {
        return res;
    }
    res = print_links(node, file);
    if (res != 0) {
        return res;
    }
    res = fputs("</DirectedGraph>\n", file);
    if (res == EOF) {
        return EOF;
    }
    return 0;
}