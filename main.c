#include <stdio.h>
#include <malloc.h>

#include "ast/ast_node_type.h"
#include "ast/ast_node.h"
#include "parser/parser.h"

int main()
{
    struct AstNode* ast = parse();
    if (ast == NULL) {
        return -1;
    }

    printf("Ast type = %s\n", ast_type_to_string[ast->type]);
    

    ast_node_destructor(&ast);
    
    return 0;
}