#include <stdio.h>
#include <malloc.h>

#include "ast/ast_node_type.h"
#include "ast/ast_node.h"
#include "parser/parser.h"

int handle_files(int argc, char** argv)
{
    for (int i = 1; i < argc; i++) {
        FILE* input_file = fopen(argv[i], "r");
        if (input_file == NULL) {
            printf("Error while opening file: %s\n", argv[i]);
            return -1;
        }

        struct AstNode* ast = parse(input_file);
        if (ast == NULL) {
            fclose(input_file);
            return -2;
        }   

        printf("Ast type = %s\n", ast_type_to_string[ast->type]);
        ast_node_destructor(&ast);
        fclose(input_file);
    }
    
    return 0;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        puts("Invalid input. Expected: ./main <path_to_file>");
        return -1;
    }
    
    return handle_files(argc, argv);
}
