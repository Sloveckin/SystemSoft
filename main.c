#include <stdio.h>
#include <malloc.h>

#include "ast/ast_node.h"
#include "backend/common/function.h"
#include "backend/common/signature.h"
#include "backend/program.h"
#include "backend/semantic_analysis/semantic_analysis.h"
#include "backend/semantic_analysis/semantic_analysis_context.h"
#include "colc/cstring.h"
#include "colc/map.h"
#include "colc/vector.h"
#include "parser/parser.h"
#include "user_input.h"
#include "dgml/from_ast.h"

static FILE* create_dgml_file(const char* file_name)
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

static int draw_ast_graph(struct AstNode* ast, const char* file_name)
{
    FILE* dgml_file = create_dgml_file(file_name);
    if (dgml_file == NULL) {
        puts("Error while writing .dmgl file");
        return -1;
    }

    int err = from_ast_to_dgml(ast, dgml_file);
    if (err != 0) {
        puts("Error while writing .dmgl file");
        fclose(dgml_file);
        return err;
    }

    fclose(dgml_file);
    return 0;
}

static int handle_file(CString* file_name, bool print_ast, bool print_log)
{   
    FILE* input_file = fopen(file_name->buffer, "r");
    if (input_file == NULL) {
        printf("Error while opening file: %s\n", file_name->buffer);
        return -1;
    }

    struct AstNode* root = parse(input_file);
    fclose(input_file);
    if (root == NULL) {
        return -2;
    }

    if (print_ast == true) {
        int err = draw_ast_graph(root, file_name->buffer);
        if (err != 0) {
            ast_node_destructor(&root);
            return err;
        }
    }

    struct AstNode** source_item_nodes = vector_get(&root->children, 0);
    if (*source_item_nodes == NULL) {
        ast_node_destructor(&root);
        return 0;
    }

    struct Program program;
    int err = program_init(&program);
    if (err != 0) {
        ast_node_destructor(&root);
        return err;
    }
    
    for (size_t j = 0; j < (*source_item_nodes)->children.size; j++) {
        struct AstNode** pointer = vector_get(&(*source_item_nodes)->children, j);
        struct AstNode* function_node = *pointer;

        if (function_node->type == AST_TYPE_FUNC_SIGNATURE) {
            struct Signature* signature = malloc(sizeof(struct Signature));
            if (signature == NULL) {
                program_free(&program);
                ast_node_destructor(&root);
                return -1;
            }

            int err = signature_init(signature, function_node);
            if (err) {
                free(signature);
                program_free(&program);
                ast_node_destructor(&root);
            }

            CString signature_name;
            err = cstring_init(&signature_name, signature->name);
            if (err != 0) {
                signature_ptr_free(signature);
                program_free(&program);
                ast_node_destructor(&root);
                return err;
            }
            
            err = map_insert(&program.signatures_ptr, &signature_name, &signature);
            if (err != 0) {
                signature_ptr_free(signature);
                program_free(&program);
                ast_node_destructor(&root);
            }

            cstring_free(&signature_name);
            continue;
        }
        
        struct Function* function = malloc(sizeof(struct Function));
        if (function == NULL) {
            program_free(&program);
            ast_node_destructor(&root);
            return -1;
        }

        int err = function_init(function, function_node);
        if (err != 0) {
            program_free(&program);
            function_free(function);
            ast_node_destructor(&root);
            return err;
        }

        CString function_name;
        err = cstring_init(&function_name, function->signature.name);
        if (err != 0) {
            program_free(&program);
            cstring_free(&function_name);
            ast_node_destructor(&root);
            return err;
        }

        err = map_insert(&program.functions_ptr, &function_name, &function);
        if (err != 0) {
            program_free(&program);
            cstring_free(&function_name);
            ast_node_destructor(&root);
            return err;
        }

        cstring_free(&function_name);
    }
    

    err = program_semantic_analysis(&program);
    if (err != 0) {
        program_free(&program);
        ast_node_destructor(&root);
        return err;
    }

    program_free(&program);
    ast_node_destructor(&root);
    return 0;
}

static int handle_files(struct UserInput* user_input)
{
    const enum Flag ast_flag = AstGraph;
    bool draw_ast_tree = vector_contains(&user_input->flags, &ast_flag, flag_compare);

    for (size_t i = 0; i < user_input->input_files.size; i++) {
        CString* file_name = vector_get(&user_input->input_files, i);
        int err = handle_file(file_name, draw_ast_tree, user_input->print_log);
        if (err != 0) {
            return err;
        }
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
