%{

#include <stdio.h>

#include "../include/ast/ast_node.h"

int yylex();
void yyerror(struct AstNode**, char*);

%}

%locations
%define parse.error verbose

%union {
    struct AstNode* node;
}

%parse-param { struct AstNode** root }


%token <node> DEC
%token <node> BOOL
%token <node> STR
%token <node> HEX
%token <node> BITS

%type <node> literal
%type <node> start

%%

start: literal { *root = $1; $$ = $1; }

literal: BOOL { $$ = $1; }
        |  DEC { $$ = $1; } 
        |  STR { $$ = $1; }
        |  HEX { $$ = $1; }
        | BITS { $$ = $1; }
;

%%

void yyerror(struct AstNode** node, char* error)
{
    printf("Error = %s\n", error);
}
