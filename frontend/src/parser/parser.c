#include "parser/parser.h"

#include <malloc.h>

#include "ast/ast_node.h"
#include "ast/ast_node_type.h"
#include "parser.tab.h"

extern FILE *yyin;
extern int yylex_destroy();

struct AstNode* parse(FILE* file)
{
    yyin = file;
    struct AstNode* ast_result = malloc(sizeof(struct AstNode));
    if (ast_result == NULL) {
        return NULL;
    }
    ast_node_init(ast_result, AST_TYPE_ROOT);
    int res = yyparse(ast_result);
    if (res != 0) {
        yylex_destroy();
        ast_node_destructor(&ast_result);
        return NULL;
    }

    yylex_destroy();

    return ast_result;
}