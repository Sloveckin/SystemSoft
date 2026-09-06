#include <stdio.h>
#include <malloc.h>

#include "ast/ast_node.h"
#include "backend/asm/riscv/asm_line.h"
#include "colc/linked_list.h"
#include "dgml/from_cfg.h"

#include "language/common/signature.h"
#include "language/program.h"
#include "language/semantic_analysis/semantic_analysis.h"
#include "language/semantic_analysis/semantic_analysis_context.h"
#include "colc/cstring.h"
#include "colc/map.h"
#include "colc/vector.h"
#include "middleend/include/middleend/cfg.h"
#include "parser/parser.h"
#include "user_input.h"
#include "dgml/from_ast.h"

static FILE* create_file(const char* file_name, const char* extenstion, const char* mode)
{
    const size_t file_name_len = strlen(file_name) + strlen(extenstion) + 2;
    char* full_file_name = malloc(file_name_len * sizeof(char));
    if (full_file_name == NULL) {
        printf("Error while creating %s.%s file\n", file_name, extenstion);
        return NULL;
    }
    sprintf(full_file_name, "%s.%s", file_name, extenstion);

    FILE* file = fopen(full_file_name, mode);
    if (file == NULL) {
        printf("Error while creating %s.%s file\n", file_name, extenstion);
        free(full_file_name);
        return NULL;
    }

    free(full_file_name);
    return file;
}

static FILE* create_dgml_file(const char* file_name)
{
    return create_file(file_name, "dgml", "w");
}

static FILE* create_asm_file(const char* file_name)
{
    return create_file(file_name, "s", "wa");
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

static int draw_control_flow_graph(const char* function_name, struct CfgNode* cfg, const char* file_name)
{
    FILE* dgml_file = create_dgml_file(file_name);
    if (dgml_file == NULL) {
        puts("Error while writing .dmgl file");
        return -1;
    }

    int err = from_cfg_to_dgml(function_name, cfg, dgml_file);
    if (err != 0) {
        puts("Error while writing .dmgl file");
        fclose(dgml_file);
        return err;
    }

    fclose(dgml_file);
    return 0;
}

static int draw_all_control_flow_graph(struct Program* program, const char* file_name)
{
    for (size_t i = 0; i < program->functions_ptr.capacity; i++) {
        if (program->functions_ptr.buffer[i].key == NULL) {
            continue;
        }
        
        struct Function** pointer = program->functions_ptr.buffer[i].value;
        struct Function* function = *pointer;

        const size_t file_name_length = strlen(file_name);
        const size_t function_name_lenght = strlen(function->signature.name);

        char* name = malloc((file_name_length + function_name_lenght + 2) * sizeof(char));
        if (file_name == NULL) {
            return -1;
        }
        sprintf(name, "%s.%s", file_name, function->signature.name);

        int err = draw_control_flow_graph(function->signature.name, function->cfg, name);
        if (err != 0) {
            free(name);
            return err;
        }

        free(name);
    }

    return 0;
}

static int write_all_into_asm_file(struct Program* program, const char* file_name) 
{
    FILE* file = create_asm_file(file_name);
    if (file == NULL) {
        return -1;
    }

    for (size_t i = 0; i < program->functions_ptr.capacity; i++) {
        if (program->functions_ptr.buffer[i].key == NULL) {
            continue;
        }

        struct Function** pointer = program->functions_ptr.buffer[i].value;
        struct Function* function = *pointer;

        // Write instructions from main list
        LinkedListNode* cur_node = linked_head(&function->riscv_context->instruction_list);
        while (cur_node != NULL) {
            struct RiscVLine *line = cur_node->memory;
            int err = write_riscv_line(line, file);
            if (err != 0) {
                return err;
            }
            cur_node = cur_node->next;
        }

        // Write instructions from return block
        cur_node = linked_head(&function->riscv_context->return_instruction_list);
        while (cur_node != 0) {
            struct RiscVLine* line = cur_node->memory;
            int err = write_riscv_line(line, file);
            if (err != 0) {
                return err;
            }
            cur_node = cur_node->next;
        }
        int res = fputs("\n", file);
        if (res < 0) {
            return res;
        }
    }
    return 0;
}

static int handle_file(const CString* file_name, const bool print_ast, const bool print_log, const bool write_cfg)
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

            int err = signature_init(signature, function_node, &program);
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

        int err = function_init(function, &program, function_node);
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
    
    bool semantic_error = false;
    err = program_semantic_analysis(&program, &semantic_error);
    if (err != 0) {
        program_free(&program);
        ast_node_destructor(&root);
        return err;
    }

    if (semantic_error == true) {
        program_free(&program);
        ast_node_destructor(&root);
        return -2; 
    }

    err = program_control_flow_graph(&program);
    if (err != 0) {
        program_free(&program);
        ast_node_destructor(&root);
        return err;
    }

    if (write_cfg == true) {
        err = draw_all_control_flow_graph(&program, file_name->buffer);
        if (err != 0) {
            program_free(&program);
            ast_node_destructor(&root);
            return err;
        }
    }

    err = program_generate_asm(&program);
    if (err != 0) {
        program_free(&program);
        ast_node_destructor(&root);
        return err;
    }

    err = write_all_into_asm_file(&program, file_name->buffer);
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
        int err = handle_file(file_name, draw_ast_tree, user_input->print_log, user_input->write_cfg);
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
