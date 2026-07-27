#include "backend/semantic_analysis/semantic_analysis.h"

#include <endian.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <threads.h>

#include "ast/ast_node.h"
#include "ast/ast_node_type.h"
#include "backend/common/signature.h"
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
    } else if (node->type == AST_TYPE_UINT_TYPE) {
        return TYPE_UINT;
    } else if (node->type == AST_TYPE_BOOL_TYPE) {
        return TYPE_BOOL;
    } else if (node->type == AST_TYPE_LONG_TYPE) {
        return TYPE_LONG;
    } else if (node->type == AST_TYPE_ULONG_TYPE) {
        return TYPE_ULONG;
    } else if (node->type == AST_TYPE_STRING_TYPE) {
        return TYPE_ULONG;
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
    union ErrorData data;
    strcpy(data.text, key->buffer);
    error_init(&error, ERROR_VARIABLE_ALREADY_EXISTS, data);

    int err = vector_push(errors, &error);
    return err;
}

static bool check_variable_not_exist_by_name(CString* key, Map* map, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    struct Variable* has_variable = map_get(map, key);
    return has_variable == NULL;
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

    struct Signature* signature = malloc(sizeof(struct Signature));
    if (signature == NULL) {
        return -1;
    }

    int res = signature_init(signature, node);
    if (res != 0) {
        free(signature);
        return res;
    }
    CString function_name;
    res = cstring_init(&function_name, signature->name);
    if (res != 0) {
        signature_free(signature);
        return res;
    }

    res = map_insert(ctx->signatures, &function_name, &signature);
    if (res != 0) {
        signature_free(signature);
        cstring_free(&function_name);
        return res;
    }

    cstring_free(&function_name);
    return 0;
}

static int check_is_variable(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, bool* error_occur, enum Type* lvalue_type)
{
    CString variable_name;
    int err = cstring_init(&variable_name, node->text);
    if (err != 0) {
        return err;
    }

    *error_occur = check_variable_not_exist_by_name(&variable_name, &ctx->arguments, errors, ctx);

    // Mean that find varaible
    if (*error_occur == false) {
        struct Variable* variable = map_get(&ctx->arguments, &variable_name);
        *lvalue_type = variable->type;
        cstring_free(&variable_name);
        return 0;
    }

    *error_occur = check_variable_not_exist_by_name(&variable_name, &ctx->variables, errors, ctx);

    if (*error_occur == false) {
        struct Variable* variable = map_get(&ctx->variables, &variable_name);
        *lvalue_type = variable->type;
        cstring_free(&variable_name);
        return 0;
    }

    struct Error error;
    union ErrorData data;
    strcpy(data.text, node->text);
    error_init(&error, ERROR_TYPE_VARIABLE_NOT_EXISTS, data);

    err = vector_push(errors, &error);
    if (err != 0) {
        cstring_free(&variable_name);
        return err;
    }

    cstring_free(&variable_name);
    return 0;
}

static int is_lvalue(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, bool *error_occur, enum Type *lvalue_type)
{
    if (node->type == AST_TYPE_IDENTIFIER) {
        return check_is_variable(node, errors, ctx, error_occur, lvalue_type);
    }
    *error_occur = true;
    struct Error error;
    union ErrorData data;
    strcpy(data.text, node->text);
    error_init(&error, ERROR_TYPE_NOT_LVALUE, data);
    

    int err = vector_push(errors, &error);
    return err;
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


static int analyze_rvalue(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, bool* error_occur, enum Type* type);

static int analyze_left_and_right(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, bool* error_occur, enum Type* left_type, enum Type* right_type)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* left = *pointer;

    int err = analyze_rvalue(left, errors, ctx, error_occur, left_type);
    if (err) {
        return err;
    }

    if (*error_occur == true) {
        return 0;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* right = *pointer;

    err = analyze_rvalue(right, errors, ctx, error_occur, right_type);
    if (err) {
        return err;
    }

    if (*error_occur == true) {
        return 0;
    }
    

    if (types_suitable(*left_type, *right_type) == false) {
        struct Error error;
        union ErrorData data = {
            .types = {
                .first_type = *left_type,
                .second_type = *right_type,
            }
        };
        error_init(&error, ERROR_TYPE_INVALID_TYPE, data);

        int err = vector_push(errors, &error);
        if (err) {
            return err;
        }

        *error_occur = true;
        return 0;
    }
    
    *error_occur = false;
    return 0;
}

static int analyze_binary_comparing(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, bool* error_occur, enum Type* type)
{
    enum Type left_type;
    enum Type right_type;
    int err = analyze_left_and_right(node, errors, ctx, error_occur, &left_type, &right_type);
    if (err != 0) {
        return 0;
    }

    if (*error_occur == true) {
        return 0;
    } 

    // No reason to check right type, because types are suitable
    if (type_is_comparable(left_type) == false) {
        struct Error error;
        union ErrorData data = {
            .type = left_type,
        };
        error_init(&error, ERROR_TYPE_TYPE_NOT_SUPPORT_ORDER, data);
        err = vector_push(errors, &error);
        if (err) {
            return err;
        }
        *error_occur = true;
        return 0;
    }

    *type = TYPE_BOOL;
    return 0;
}

static int analyze_binary_operation(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, bool* error_occur, enum Type* type, const bool is_boolean_operation)
{
    enum Type left_type;
    enum Type right_type;
    int err = analyze_left_and_right(node, errors, ctx, error_occur, &left_type, &right_type);
    if (err != 0) {
        return 0;
    }

    if (*error_occur == true) {
        return 0;
    } 

    // No reason to check right type, because types are suitable
    if (is_boolean_operation == true && type_support_boolean_operations(left_type) == false
        || is_boolean_operation == false && type_support_arithmetic_operations(left_type) == false) {
        struct Error error;
        union ErrorData data = {
            .type = *type,
        };
        enum ErrorType error_type;
        if (is_boolean_operation) {
            error_type = ERROR_TYPE_TYPE_NOT_SUPPORT_BOOLEAN_OPERATIONS;
        } else {
            error_type = ERROR_TYPE_TYPE_NOT_SUPPORT_ARITHMETIC_OPERATIONS;
        }

        error_init(&error, error_type, data);

        err = vector_push(errors, &error);
        if (err) {
            return err;
        }
        *error_occur = true;
        return 0;
    }

    if (is_boolean_operation == false) {
        if (right_type > left_type) {
            *type = right_type;
        } else {
            *type = left_type;
        }
    } else {
        *type = TYPE_BOOL;
    }

    return 0;
}

static int analyze_variable_like_rvalue(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, bool* error_occur, enum Type* type)
{
    CString name;
    int err = cstring_init(&name, node->text);
    if (err) {
        return err;
    }

    struct Variable* variable = get_variable_by_name(ctx, &name);
    if (variable == NULL) {
        struct Error error;
        union ErrorData data;
        strcpy(data.text, node->text);
        error_init(&error, ERROR_TYPE_VARIABLE_NOT_EXISTS, data);

        *error_occur = true;
        err = vector_push(errors, &error);
        cstring_free(&name);
        return err;
    }

    *error_occur = false;
    *type = variable->type;

    cstring_free(&name);
    return 0;
}

static bool is_callable(struct AstNode* node) {
    return node->type == AST_TYPE_IDENTIFIER;
}

static int analyze_call_arguments(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, bool* error_occur, struct Signature* signature)
{
    size_t arguments_amount = 0;
    if (node != NULL) {
        arguments_amount = node->children.size;
    }


    if (signature->arguments.size != arguments_amount) {
        *error_occur = true;

        struct Error error;
        union ErrorData data = {
            .argument_amount.expected = signature->arguments.size,
            .argument_amount.provided = arguments_amount,
        };
        error_init(&error, ERROR_TYPE_INVALID_AMOUNT_OF_ARGUMENTS, data);
        return vector_push(errors, &error);
    }

    for (size_t i = 0; i < signature->arguments.size; i++) {
        struct AstNode** pointer = vector_get(&node->children, i);
        struct AstNode* arg = *pointer;

        enum Type arg_type;
        int err = analyze_rvalue(arg, errors, ctx, error_occur, &arg_type);
        if (err) {
            return err;
        }

        if (*error_occur == true) {
            return 0;
        } 

        struct Variable* signature_argument = vector_get(&signature->arguments, i);

        if (types_suitable(arg_type, signature_argument->type) == false) {
            struct Error error;
            union ErrorData data = {
                .types.first_type = arg_type,
                .types.second_type = signature_argument->type,
            };
            error_init(&error, ERROR_TYPE_INVALID_TYPE, data);

            err = vector_push(errors, &error);
            return err;
        }
    }
    
    return 0;
}

static int analyze_function_call(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, bool* error_occur, enum Type* type)
{
    assert(node->type == AST_TYPE_CALL_OR_INDEXER);

    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* caller_node = *pointer;

    pointer = vector_get(&node->children, 1);
    struct AstNode* args_node = *pointer;

    const bool can_call = is_callable(caller_node);
    if (can_call == false) {

        struct Error error;
        union ErrorData data;
        strcpy(data.text, caller_node->text);
        error_init(&error, ERROR_TYPE_NOT_CALLABLE_OR_INDEXER, data);

        int err = vector_push(errors, &error);
        if (err != 0) {
            return err;
        }

        *error_occur = true;
        return 0;
    }

    CString variable_name;
    int err = cstring_init(&variable_name, caller_node->text);
    if (err != 0) {
        return err;
    }

    struct Variable* variable = get_variable_by_name(ctx, &variable_name);
    if (variable != NULL) {
        *type = variable->type;
        cstring_free(&variable_name);
        return 0;
    }

    struct Signature* signature = get_signature_by_name(ctx, &variable_name);
    if (signature != NULL) {
        int err = analyze_call_arguments(args_node, errors, ctx, error_occur, signature);
        if (*error_occur == true) {
            cstring_free(&variable_name);
            return 0;
        }

        *type = signature->return_type;
        cstring_free(&variable_name);
        return 0;
    }

    *error_occur = true;

    struct Error error;
    union ErrorData data;
    strcpy(data.text, variable_name.buffer);
    error_init(&error, ERROR_TYPE_FUNCTION_NOT_EXISTS, data);

    err = vector_push(errors, &error);
    cstring_free(&variable_name);
    return err;
}


static int analyze_rvalue(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, bool* error_occur, enum Type* type)
{
    if (node->type == AST_TYPE_DEC) {
        *error_occur = false;
        *type = TYPE_INT;
    } else if (node->type == AST_TYPE_BOOL) {
        *error_occur = false;
        *type = TYPE_BOOL;
    } else if (node->type == AST_TYPE_STR) {
        *error_occur = false;
        *type = TYPE_STRING;
    } else if (node->type == AST_TYPE_IDENTIFIER) {
        int err = analyze_variable_like_rvalue(node, errors, ctx, error_occur, type);
        if (err) {
            return err;
        }
    } else if (node->type == AST_TYPE_PLUS || node->type == AST_TYPE_MINUS || node->type == AST_TYPE_MUL || node->type == AST_TYPE_DIV) {
        int err = analyze_binary_operation(node, errors, ctx, error_occur, type, false);
        if (err != 0) {
            return err;
        }
    } else if (node->type == AST_TYPE_OR || node->type == AST_TYPE_AND) {
        int err = analyze_binary_operation(node, errors, ctx, error_occur, type, true);
        if (err != 0) {
            return err;
        }
    } else if (node->type == AST_TYPE_MORE || node->type == AST_TYPE_LESS || node->type == AST_TYPE_EQ || node->type == AST_TYPE_NOT_EQ) {
        int err = analyze_binary_comparing(node, errors, ctx, error_occur, type);
        if (err != 0) {
            return err;
        }
    } else if (node->type == AST_TYPE_CALL_OR_INDEXER) {
        int err = analyze_function_call(node, errors, ctx, error_occur, type);
        if (err != 0) {
            return err;
        }
    } else {
        assert (0);
    }

    return 0;
}

static int analyze_assigmnet(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* left = *pointer;
    bool error_occur = false;
    enum Type lvalue_type;
    int err = is_lvalue(left, errors, ctx, &error_occur, &lvalue_type);
    if (err != 0) {
        return err;
    }
    // No reason to continue analyze assigment
    if (error_occur) {
        return 0;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* right = *pointer;

    enum Type rvalue_type;
    err = analyze_rvalue(right, errors, ctx, &error_occur, &rvalue_type);
    if (err != 0) {
        return err;
    }

    if (error_occur == true) {
        return 0;
    }

    if (types_suitable(lvalue_type, rvalue_type) == false) {
        struct Error invalid_type_error;
        union ErrorData data = {
            .types = {
                .first_type = lvalue_type,
                .second_type = rvalue_type,
            },
        };
        error_init(&invalid_type_error, ERROR_TYPE_INVALID_TYPE, data);
        
        err = vector_push(errors, &invalid_type_error);
        if (err) {
            return err;
        }
    }
    
    return 0;
}


static int analyze_cycle_or_if(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx, const size_t index)
{
    struct AstNode** pointer = vector_get(&node->children, index);
    struct AstNode* expr_node = *pointer;

    bool error_occur = false;
    enum Type rvalue_type;
    int err = analyze_rvalue(expr_node, errors, ctx, &error_occur, &rvalue_type);
    if (err != 0) {
        return err;
    }

    if (error_occur == true) {
        return 0;
    }

    if (rvalue_type != TYPE_BOOL) {
        struct Error invalid_type_error;
        union ErrorData data = {
            .types = {
                .first_type = TYPE_BOOL,
                .second_type = rvalue_type,
            },
        };
        error_init(&invalid_type_error, ERROR_TYPE_INVALID_TYPE, data);
        
        err = vector_push(errors, &invalid_type_error);
        if (err) {
            return err;
        }
    }

    return 0;
}

static int analyze_do_cycle(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    ctx->cycle_counter++;
    int res = analyze_cycle_or_if(node, errors, ctx, 2);
    ctx->cycle_counter--;
    return res;
}

static int analyze_while_cycle(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
   ctx->cycle_counter++;
    int res = analyze_cycle_or_if(node, errors, ctx, 0);
    ctx->cycle_counter--;
    return res;
}

static int analyze_if(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    return analyze_cycle_or_if(node, errors, ctx, 0);
}

static int analyze_break(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    if (ctx->cycle_counter > 0) {
        return 0;
    }

    struct Error error;
    union ErrorData data;
    error_init(&error, ERROR_TYPE_BREAK_OUTSIDE_OF_CYCLE, data);

    return vector_push(errors, &error);
}

static int analyze_statement(struct AstNode* node, Vector* errors, struct SemanticAnalysisContext* ctx)
{
    if (node->type == AST_TYPE_ASSIGMENT) {
       return analyze_assigmnet(node, errors, ctx);
    } else if (node->type == AST_TYPE_VAR) {
        return analyze_variable_creation(node, errors, ctx);
    } else if (node->type == AST_TYPE_DO) {
        return analyze_do_cycle(node, errors, ctx);
    } else if (node->type == AST_TYPE_WHILE_CYCLE) {
        return analyze_while_cycle(node, errors, ctx);
    } else if (node->type == AST_TYPE_IF_BLOCK) {
        return analyze_if(node, errors, ctx);
    } else if (node->type == AST_TYPE_BREAK) {
        return analyze_break(node, errors, ctx);
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

    if (node->type == AST_TYPE_FUNC_DEF) {
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

    return analyze_signature(node, errors, ctx);
}
