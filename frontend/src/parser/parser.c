#include "parser/parser.h"

#include <malloc.h>

#include "ast/ast_node.h"
#include "parser.tab.h"

extern FILE *yyin;
extern int yylex_destroy();

struct AstNode* parse(FILE* file)
{
    yyin = file;
    struct AstNode* ast_result = malloc(sizeof(struct AstNode));
    int res = yyparse(ast_result);
    if (res != 0) {
        yylex_destroy();
        free(ast_result);
        return NULL;
    }

    yylex_destroy();

    return ast_result;
}