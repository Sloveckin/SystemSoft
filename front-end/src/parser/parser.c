#include "parser/parser.h"

#include <malloc.h>

#include "ast/ast_node.h"
#include "parser.tab.h"

extern FILE *yyin;

struct AstNode* parse(FILE* file)
{
    yyin = file;
    struct AstNode* ast_result = NULL;
    int res = yyparse(&ast_result);
    if (res != 0) {
        free(ast_result);
        return NULL;
    }

    return ast_result;
}