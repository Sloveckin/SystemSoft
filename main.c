#include <stdio.h>
#include <malloc.h>

#include "ast/ast_node.h"
#include "parser/parser.h"

int main()
{
    struct AstNode* ast = parse();
    if (ast == NULL) {
        return -1;
    }

    ast_node_destructor(ast);
    return 0;
}