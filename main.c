#include <stdio.h>
#include <malloc.h>

#include "ast/ast_node_type.h"
#include "ast/ast_node.h"
#include "colc/cstring.h"
#include "colc/vector.h"
#include "dgml/include/dgml/ast.h"
#include "parser/parser.h"
#include "user_input.h"
#include "dgml/ast.h"

FILE* create_dgml_file(const char* file_name)
{
    const size_t len_dgml_file_name = strlen(file_name) + 6;
    char* dgml_file_name = malloc(len_dgml_file_name * sizeof(char));
    sprintf(dgml_file_name, "%s.dgml", file_name);
    if (dgml_file_name == NULL) {
        printf("Error while creating %s.dmgl file\n", file_name);
        return NULL;
    }

    FILE* dgml_file = fopen(dgml_file_name, "w");
    if (dgml_file == NULL) {
        printf("Error while creating %s.dmgl file\n", file_name);
        free(dgml_file_name);
        return NULL;
    }

    free(dgml_file_name);
    return dgml_file;
}

int handle_files(struct UserInput* user_input)
{
    const enum Flag ast_flag = AstGraph;
    bool draw_ast_tree = vector_contains(&user_input->flags, &ast_flag, flag_compare);

    for (size_t i = 0; i < user_input->input_files.size; i++) {
        CString* file_name = vector_get(&user_input->input_files, i);
        FILE* input_file = fopen(file_name->buffer, "r");
        if (input_file == NULL) {
            printf("Error while opening file: %s\n", file_name->buffer);
            return -1;
        }

        struct AstNode* ast = parse(input_file);
        if (ast == NULL) {
            fclose(input_file);
            return -2;
        }   
        
        if (draw_ast_tree) {
            FILE* dgml_file = create_dgml_file(file_name->buffer);
            if (dgml_file == NULL) {
                return -1;
            }

            int err = from_ast_to_dgml(ast, dgml_file);
            if (err != 0) {
                ast_node_destructor(&ast);
                fclose(input_file);
                fclose(dgml_file);
                return err;
            }

            fclose(dgml_file);
        }
        
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

    struct UserInput user_input;
    int res = user_input_init(&user_input);
    if (res != 0) {
        return res;
    }

    res = read_user_input(&user_input, argc, argv);
    if (res != 0) {
        user_input_free(&user_input);
        return res;
    }
    
    res = handle_files(&user_input);
    user_input_free(&user_input);
    return res;
}
