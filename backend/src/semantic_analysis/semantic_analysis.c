#include "backend/semantic_analysis/semantic_analysis.h"

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "ast/ast_node.h"
#include "ast/ast_node_type.h"
#include "backend/common/variable.h"
#include "backend/error/error.h"
#include "backend/semantic_analysis/semantic_analysis_context.h"
#include "backend/type/type.h"
#include "colc/cstring.h"
#include "colc/map.h"
#include "colc/vector.h"


static char* get_text(struct AstNode* node)
{
    assert(node->type == AST_TYPE_IDENTIFIER);
    const size_t text_len = strlen(node->text) + 1;
    char* text = malloc(text_len * sizeof(char));
    if (text == NULL) {
        return NULL;
    }
    strcpy(text, node->text);

    return text;
}

static enum Type get_type(struct AstNode* node)
{
    if (node->type == AST_TYPE_INT_TYPE) {
        return TYPE_INT;
    }

    assert(0);
}

static int check_variable_exist_by_name(CString* key, Map* map, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    struct Variable* has_variable = map_get(map, key);
    if (has_variable == NULL) {
        return 0;
    }
    struct Error error;
    int err = error_init(&error, ERROR_VARIABLE_ALREADY_EXISTS, key->buffer);
    if (err != 0) {
        return err;
    }

    err = vector_push(errors, &error);
    error_free(&error);
    return err;
}

static int analyze_arg_def(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    assert(node->type == AST_TYPE_ARG_DEF);

    struct AstNode **pointer = vector_get(&node->children, 0);
    struct AstNode* variable_name_node = *pointer;
    char* variable_name = get_text(variable_name_node);
    if (variable_name == NULL) {
        return -1;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* type_node = *pointer;
    const enum Type type = get_type(type_node);

    struct Variable variable;
    variable_init(&variable, variable_name, type);

    CString key;
    int err = cstring_init(&key, variable_name);
    if (err != 0) {
        variable_free(&variable);
        return err;
    }

    /*struct Variable* has_variable = map_get(&ctx->arguments, &key);
    if (has_variable != NULL) {
        struct Error error;
        int err = error_init(&error, ERROR_VARIABLE_ALREADY_EXISTS, key.buffer);
        if (err != 0) {
            cstring_free(&key);
            variable_free(&variable);
            return err;
        }

        err = vector_push(errors, &error);

        cstring_free(&key);
        variable_free(&variable);
        error_free(&error);
        return err;
    }*/

    err = check_variable_exist_by_name(&key, &ctx->arguments, errors, ctx);
    if (err != 0) {
        cstring_free(&key);
        variable_free(&variable);
        return err;
    }

    err = map_insert(&ctx->arguments, &key, &variable);
    cstring_free(&key);
    variable_free(&variable);
    return err;
}

static int analyze_signature_arguments(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    if (node == NULL) {
        return 0;
    }
    assert(node->type == AST_TYPE_ARG_DEF_LIST);

    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** pointer = vector_get(&node->children, i);
        struct AstNode* arg_def_node = *pointer;
        int err = analyze_arg_def(arg_def_node, errors, ctx);
        if (err != 0) {
            return err;
        }
    }
    
    return 0;
}

static int analyze_signature(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    assert(node->type == AST_TYPE_FUNC_SIGNATURE);
    struct AstNode **pointer;
    pointer = vector_get(&node->children, 1);
    struct AstNode* arg_def_list_node = *pointer;
    int err = analyze_signature_arguments(arg_def_list_node, errors, ctx);
    if (err != 0) {
        return err;
    }
    return 0;
}

static int is_lvalue(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    if (node->type == AST_TYPE_IDENTIFIER) {
        assert(0);
    }
    struct Error error;
    int err = error_init(&error, ERROR_TYPE_NOT_LVALUE, node->text);
    if (err != 0) {
        return err;
    }

    err = vector_push(errors, &error);
    if (err != 0) {
        error_free(&error);
        return err;
    }

    error_free(&error);
    return 0;
}

static int analyze_identifier_list(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, const enum Type type)
{
    for (size_t i = 0; i < node->children.size; i++) {

        struct AstNode** pointer = vector_get(&node->children, i);
        struct AstNode* name_node = *pointer;

        char* name = get_text(name_node);

        struct Variable variable;
        variable_init(&variable, name, type);
        

        CString variable_name;
        int err = cstring_init(&variable_name, variable.name);
        if (err != 0) {
            variable_free(&variable);
            return err;
        }

        // struct Variable* variable_pointer = map_get(&ctx->arguments, &variable_name);
        // if (variable_pointer != NULL) {
        //     struct Error error;
        //     int err = error_init(&error, ERROR_VARIABLE_ALREADY_EXISTS, variable_pointer->name);
        //     if (err != 0) {
        //         cstring_free(&variable_name);
        //         variable_free(&variable);
        //         return err;
        //     }

        //     err = vector_push(errors, &error);

        //     error_free(&error);
        //     cstring_free(&variable_name);
        //     variable_free(&variable);
        //     return err;
        // }

        err = check_variable_exist_by_name(&variable_name, &ctx->arguments, errors, ctx);
        if (err != 0) {
            cstring_free(&variable_name);
            variable_free(&variable);
            return err;
        }

        err = check_variable_exist_by_name(&variable_name, &ctx->variables, errors, ctx);
        if (err != 0) {
            cstring_free(&variable_name);
            variable_free(&variable);
            return err;
        }

        err = map_insert(&ctx->variables, &variable_name, &variable);
        if (err != 0) {
            cstring_free(&variable_name);
            variable_free(&variable);
            return err;
        }


        cstring_free(&variable_name);
        variable_free(&variable);
    }

    return 0;
}

static int analyze_variable_creation(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    struct AstNode** pointer = vector_get(&node->children, 1);
    struct AstNode* type_node = *pointer;

    const enum Type type = get_type(type_node);

    pointer = vector_get(&node->children, 0);
    struct AstNode* identifier_list_node = *pointer;

    int err = analyze_identifier_list(identifier_list_node, errors, ctx, type);
    if (err != 0) {
        return err;
    }

    return 0;
}

static int analyze_statement(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    if (node->type == AST_TYPE_ASSIGMENT) {
        struct AstNode** pointer = vector_get(&node->children, 0);
        struct AstNode* left = *pointer;
        int err = is_lvalue(left, errors, ctx);
        if (err != 0) {
            return err;
        }

        return 0;
    } else if (node->type == AST_TYPE_VAR) {
        return analyze_variable_creation(node, errors, ctx);
    }
    assert (0);
}

static int analyze_statement_list(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    // List can not exist
    if (node == NULL) {
        return 0;
    }

    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** pointer = vector_get(&node->children, i);
        struct AstNode* statement_node = *pointer;

        int err = analyze_statement(statement_node, errors, ctx);
        if (err != 0) {
            return err;
        }
    }

    return 0;
}

int semantic_analysis(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{   
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* signature_node = *pointer;

    int err = analyze_signature(signature_node, errors, ctx);
    if (err != 0) {
        return err;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* statement_list = *pointer;

    err = analyze_statement_list(statement_list, errors, ctx);
    if (err != 0) {
        return err;
    }

    return 0;
}