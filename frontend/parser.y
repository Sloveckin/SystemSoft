%{

#include <stdio.h>

#include "../include/ast/ast_node.h"
#include <assert.h>

int yylex();
void yyerror(struct AstNode*, char*);

%}

%locations
%define parse.error verbose

%union {
    struct AstNode* node;
}

%destructor { 
    if ($$) {
        ast_node_destructor(&$$);
    }
} <node>


%parse-param { struct AstNode* root }


%type source

%token <node> INT_TYPE
%token <node> BOOL_TYPE
%token <node> BYTE_TYPE
%token <node> UINT_TYPE
%token <node> LONG_TYPE
%token <node> ULONG_TYPE
%token <node> CHAR_TYPE
%token <node> STRING_TYPE

%left PLUS
%left MINUS
%left DIV
%left MUL
%left LESS
%left MORE
%left OR
%left AND
%right EQ
%right NOT_EQ
%token NOT


%token ASSIGMENT
%token AS

%token BR_OPEN
%token BR_CLOSE
%token SEMICOLON

%token COMMA
%token DO
%token LOOP
%token WEND
%token IF
%token THEN
%token ELSE
%token END
%token DIM
%token FUNCTION

%token <node> DEC
%token <node> BOOL
%token <node> STR
%token <node> HEX
%token <node> BITS
%token <node> IDENTIFIER
%token <node> BREAK
%token <node> WHILE
%token <node> UNTIL

%type <node> literal
%type <node> expr
%type <node> place
%type <node> assigment
%type <node> binary
%type <node> unary
%type <node> braces
%type <node> expression
%type <node> statement
%type <node> break
%type <node> statement_list
%type <node> expr_list
%type <node> call_or_indexer
%type <node> while_or_until
%type <node> do
%type <node> while
%type <node> if
%type <node> else_block
%type <node> else_block_opt
%type <node> builtin
%type <node> type_ref
%type <node> custom
%type <node> arg_def
%type <node> arg_def_list
%type <node> return_type_opt
%type <node> identifier_list
%type <node> var
%type <node> func_signature
%type <node> func_def
%type <node> source_item
%type <node> source_item_list
%type <node> array

%%

source: source_item_list    {
                                vector_push(&root->children, &$1);
                            }
;

statement:  var { $$ = $1; }
        |   if {$$ = $1; }
        |   while { $$ = $1; }
        |   do { $$ = $1; }
        |   break { $$ = $1; }
        |   expression { $$ = $1; }
;                                         

statement_list: %empty { $$ = NULL; }
            | statement     {
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_STATMENT_LIST);
                                vector_push(&node->children, &$1);
                                $$ = node;
                            }
            | statement_list statement  {
                                            vector_push(&$1->children, &$2);
                                            $$ = $1;
                                        }
;

source_item: func_signature { $$ = $1; }
        |    func_def { $$ = $1; }
;

source_item_list: %empty { $$ = NULL; }
            |    source_item    {
                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                    ast_node_init(node, AST_TYPE_SOURCE_ITEM_LIST);
                                    vector_push(&node->children, &$1);
                                    $$ = node;
                                }
            |   source_item_list source_item    {
                                                    vector_push(&$1->children, &$2);
                                                    $$ = $1;
                                                }
;

return_type_opt: %empty { $$ = NULL; }
            | AS type_ref { $$ = $2; }
;

func_signature: IDENTIFIER BR_OPEN arg_def_list BR_CLOSE return_type_opt    {
                                                                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                                                                ast_node_init(node, AST_TYPE_FUNC_SIGNATURE);
                                                                                vector_push(&node->children, &$1);
                                                                                vector_push(&node->children, &$3);
                                                                                vector_push(&node->children, &$5);
                                                                                $$ = node;
                                                                            }
;

func_def: FUNCTION func_signature statement_list END FUNCTION   {
                                                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                                                    ast_node_init(node, AST_TYPE_FUNC_DEF);
                                                                    vector_push(&node->children, &$2);
                                                                    vector_push(&node->children, &$3);
                                                                    $$ = node;
                                                                }
;

arg_def_list: %empty { $$ = NULL; }
            | arg_def   {
                            struct AstNode* node = malloc(sizeof(struct AstNode));
                            ast_node_init(node, AST_TYPE_ARG_DEF_LIST);
                            vector_push(&node->children, &$1);
                            $$ = node;
                        }
            | arg_def_list COMMA arg_def    {
                                                vector_push(&$1->children, &$3);
                                                $$ = $1;
                                            }
;

type_ref: custom { $$ = $1; }
        | builtin { $$ = $1; }
        | array { $$ = $1; }
;

arg_def: IDENTIFIER AS type_ref {
                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                    ast_node_init(node, AST_TYPE_ARG_DEF);
                                    vector_push(&node->children, &$1);
                                    vector_push(&node->children, &$3);
                                    $$ = node;
                                }
;

custom: IDENTIFIER { $$ = $1; }
;

var: DIM identifier_list AS type_ref    {
                                            struct AstNode* node = malloc(sizeof(struct AstNode));
                                            ast_node_init(node, AST_TYPE_VAR);
                                            vector_push(&node->children, &$2);
                                            vector_push(&node->children, &$4);
                                            $$ = node;
                                        }
;

identifier_list: IDENTIFIER 
                            {
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_IDENTIFIER_LIST);
                                vector_push(&node->children, &$1);
                                $$ = node;
                            }
            |    identifier_list COMMA IDENTIFIER {
                                                vector_push(&$1->children, &$3);
                                                $$ = $1;
                                            }  
;


array: type_ref BR_OPEN expr BR_CLOSE   {
                                            struct AstNode* node = malloc(sizeof(struct AstNode));
                                            ast_node_init(node, AST_TYPE_ARRAY);
                                            vector_push(&node->children, &$1);
                                            vector_push(&node->children, &$3);
                                            $$ = node;
                                        }
;

builtin:   INT_TYPE { $$ = $1; }
        |  BOOL_TYPE { $$ = $1; }
        |  BYTE_TYPE { $$ = $1; }
        |  UINT_TYPE { $$ = $1; }
        |  LONG_TYPE { $$ = $1; }
        |  ULONG_TYPE { $$ = $1; }
        |  CHAR_TYPE { $$ = $1; }
        |  STRING_TYPE { $$ = $1; }
;

else_block_opt: { $$ = NULL; }
            |   else_block { $$ = $1; }
;

else_block: ELSE statement_list {
                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                    ast_node_init(node, AST_TYPE_ELSE_BLOCK);
                                    vector_push(&node->children, &$2);
                                    $$ = node;
                                }
;

if: IF expr THEN statement_list else_block_opt END IF  {
                                            struct AstNode* node = malloc(sizeof(struct AstNode));
                                            ast_node_init(node, AST_TYPE_IF_BLOCK);
                                            vector_push(&node->children, &$2);
                                            vector_push(&node->children, &$4);
                                            vector_push(&node->children, &$5);
                                            $$ = node;
                                        }
;

while_or_until: WHILE { $$ = $1; }
            |   UNTIL { $$ = $1; }
;

do: DO statement_list LOOP while_or_until expr  {
                                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                                    ast_node_init(node, AST_TYPE_DO);
                                                    vector_push(&node->children, &$2);
                                                    vector_push(&node->children, &$4);
                                                    vector_push(&node->children, &$5);
                                                    $$ = node;
                                                }
;

while: WHILE expr statement_list WEND   {
                                            struct AstNode* node = malloc(sizeof(struct AstNode));
                                            ast_node_init(node, AST_TYPE_WHILE_CYCLE);
                                            vector_push(&node->children, &$2);
                                            vector_push(&node->children, &$3);
                                            ast_node_destructor(&$1);
                                            $$ = node;
                                        }

binary:  expr PLUS     expr { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_PLUS);
                                vector_push(&node->children, &$1);
                                vector_push(&node->children, &$3);
                                $$ = node;
                            }
       | expr MINUS    expr { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_MINUS);
                                vector_push(&node->children, &$1);
                                vector_push(&node->children, &$3);
                                $$ = node;
                            }
       | expr MUL      expr { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_MUL);
                                vector_push(&node->children, &$1);
                                vector_push(&node->children, &$3);
                                $$ = node;
                            }
       | expr DIV      expr { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_DIV);
                                vector_push(&node->children, &$1);
                                vector_push(&node->children, &$3);
                                $$ = node;
                            }
       | expr EQ       expr { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_EQ);
                                vector_push(&node->children, &$1);
                                vector_push(&node->children, &$3);
                                $$ = node;
                            }
       | expr NOT_EQ   expr { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_NOT_EQ);
                                vector_push(&node->children, &$1);
                                vector_push(&node->children, &$3);
                                $$ = node;
                            }
       | expr MORE     expr { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_MORE);
                                vector_push(&node->children, &$1);
                                vector_push(&node->children, &$3);
                                $$ = node;
                            }
       | expr LESS     expr { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_LESS);
                                vector_push(&node->children, &$1);
                                vector_push(&node->children, &$3);
                                $$ = node;
                            }
       | expr AND       expr { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_OR);
                                vector_push(&node->children, &$1);
                                vector_push(&node->children, &$3);
                                $$ = node;
                            }
       | expr OR      expr { 
                                struct AstNode* node = malloc(sizeof(struct AstNode));
                                ast_node_init(node, AST_TYPE_AND);
                                vector_push(&node->children, &$1);
                                vector_push(&node->children, &$3);
                                $$ = node;
                            }
;

unary:  PLUS  expr  {
                        struct AstNode* node = malloc(sizeof(struct AstNode));
                        ast_node_init(node, AST_TYPE_UNARY_PLUS);
                        vector_push(&node->children, &$2);
                        $$ = node;
                    }
      | MINUS expr  {
                        struct AstNode* node = malloc(sizeof(struct AstNode));
                        ast_node_init(node, AST_TYPE_UNARY_MINUS);
                        vector_push(&node->children, &$2);
                        $$ = node;
                    }
      | NOT  expr   {
                        struct AstNode* node = malloc(sizeof(struct AstNode));
                        ast_node_init(node, AST_TYPE_NOT);
                        vector_push(&node->children, &$2);
                        $$ = node;
                    }
;

assigment: expr ASSIGMENT expr
                                {
                                    struct AstNode* node = malloc(sizeof(struct AstNode));
                                    ast_node_init(node, AST_TYPE_ASSIGMENT);
                                    vector_push(&node->children, &$1);
                                    vector_push(&node->children, &$3);
                                    $$ = node;
                                }
;

break: BREAK { $$ = $1; }
;

expression: expr SEMICOLON { $$ = $1; }
;

braces: BR_OPEN expr BR_CLOSE { $$ = $2; }
;

expr_list: %empty { $$ = NULL; }
        | expr  {
                    struct AstNode* node = malloc(sizeof(struct AstNode));
                    ast_node_init(node, AST_TYPE_EXPR_LIST);
                    vector_push(&node->children, &$1);
                    $$ = node;
                }
        |   expr_list COMMA expr    {
                                        vector_push(&$1->children, &$3);
                                        $$ = $1;
                                    }
;

call_or_indexer: expr BR_OPEN expr_list BR_CLOSE    {
                                                        struct AstNode* node = malloc(sizeof(struct AstNode));
                                                        ast_node_init(node, AST_TYPE_CALL_OR_INDEXER);
                                                        vector_push(&node->children, &$1);
                                                        vector_push(&node->children, &$3);
                                                        $$ = node;
                                                    }
;

expr:  assigment { $$ = $1; }
    |  binary { $$ = $1; }
    |  unary { $$ = $1; }
    |  braces { $$ = $1; }
    |  call_or_indexer { $$ = $1; }
    |  place { $$ = $1; }
    |  literal { $$ = $1; }
;

place: IDENTIFIER { $$ = $1; }
;

literal: BOOL { $$ = $1; }
        |  DEC { $$ = $1; } 
        |  STR { $$ = $1; }
        |  HEX { $$ = $1; }
        | BITS { $$ = $1; }
;

%%

void yyerror(struct AstNode* node, char* error)
{
    printf("Error = %s\n", error);
}
