#include "backend/semantic_analysis/semantic_analysis.h"

#include <errno.h>
#include <endian.h>
#include <error.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

#include "ast/ast_node.h"
#include "ast/ast_node_type.h"
#include "backend/common/function.h"
#include "backend/common/signature.h"
#include "backend/common/variable.h"
#include "backend/error/error.h"
#include "backend/program.h"
#include "backend/semantic_analysis/semantic_analysis_context.h"
#include "backend/type/type.h"
#include "colc/cstring.h"
#include "colc/map.h"
#include "colc/vector.h"

static int analyze_rvalue(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, struct ExpressionInfo* expr_info);

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

static struct Type* get_type(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, int* error, bool add_to_ctx);


// TODO: rewrite this shit
static struct Type* analyze_array_type(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, int* error)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* node_type = *pointer;

    struct Type* element_type = get_type(node_type, errors, ctx,  error_occur, error, false);
    if (*error != 0) {
        return NULL;
    }

    /*int err = vector_push(&ctx->types, &element_type);
    if (err != 0) {
        *error = err;
        return NULL;
    }*/

    if (*error_occur == true) {
        *error = 0;
        return NULL;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* node_length = *pointer;

    //char* hlp_pointer;

    // unsigned long length = strtoul(node_length->text, &hlp_pointer, 10);
    // if (errno == ERANGE || *hlp_pointer != 0) {
    //     struct Error error_info;
    //     union ErrorData data;
    //     strcpy(data.text, node_length->text);
    //     error_init(&error_info, ERROR_TYPE_NOT_UNSIGNED_NUMBER, data);

    //     int err = vector_push(errors, &error_info);
    //     if (err != 0) {
    //         *error = err;
    //         return NULL;
    //     }
        
    //     return 0;
    // }
    struct ExpressionInfo expr_info;
    int err = analyze_rvalue(node_length, errors, ctx, error_occur, &expr_info);
    if (err) {
        *error = err;
        return NULL;
    }

    size_t length;
    if (expr_info.is_constant == false || 
        expr_info.is_constant == true && (expr_info.type->kind == TYPE_KIND_INT || expr_info.type->kind == TYPE_KIND_LONG) && expr_info.value.number <= 0) {
        struct Error error_info;
        union ErrorData error_data;
        
        *error_occur = true;
        error_init(&error_info, ERROR_TYPE_NOT_UNSIGNED_NUMBER, error_data);
        *error = vector_push(errors, &error_info);
        return NULL;
    } else {
        if (expr_info.type->kind == TYPE_KIND_INT || expr_info.type->kind == TYPE_KIND_LONG) {
            length = expr_info.value.number;
        } else if (expr_info.type->kind == TYPE_KIND_UINT || expr_info.type->kind == TYPE_KIND_ULONG) {
            length = expr_info.value.unumber;
        } else {
            assert(0);
        }
    }

    if (*error_occur ==  true) {
        *error = 0;
        return NULL;
    }

    struct ArrayType* array_type = malloc(sizeof(struct ArrayType));
    if (array_type == NULL) {
        *error = -1;
        return NULL;
    }

    *error = 0;

    array_type->base.kind = TYPE_KIND_ARRAY;
    array_type->element_type = element_type;
    array_type->length = length;

    return (struct Type*)array_type;
}

static struct Type* init_basic_type(enum TypeKind type_kind, int *error)
{
    struct Type* type = malloc(sizeof(struct Type));
    if (type == NULL) {
        *error = -1;
        return NULL;
    }
    type->kind = type_kind;
    
    return type;
}

static struct Type* get_type(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, int* error, bool add_to_ctx)
{
    struct Type* result;
    if (node->type == AST_TYPE_INT_TYPE) {
        result =  init_basic_type(TYPE_KIND_INT, error);
    } else if (node->type == AST_TYPE_UINT_TYPE) {
        result = init_basic_type(TYPE_KIND_UINT, error);
    } else if (node->type == AST_TYPE_BOOL_TYPE) {
        result = init_basic_type(TYPE_KIND_BOOL, error);
    } else if (node->type == AST_TYPE_LONG_TYPE) {
        result = init_basic_type(TYPE_KIND_BOOL, error);
    } else if (node->type == AST_TYPE_ULONG_TYPE) {
        result = init_basic_type(TYPE_KIND_ULONG, error);
    } else if (node->type == AST_TYPE_STRING_TYPE) {
        result = init_basic_type(TYPE_KIND_ULONG, error);
    } else if (node->type == AST_TYPE_ARRAY) {
        result = analyze_array_type(node, errors, ctx, error_occur, error);
    } else {
        assert (0);
    }
    
    if (add_to_ctx == true) {
        int err = vector_push(&ctx->types, &result);
        if (err != 0) {
            *error = err;
            return NULL;
        }
    }

    return result;
}

static int check_variable_exist_by_name(CString* key, Map* map, Vector* errors, struct SemanticContext* ctx)
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

static bool check_variable_not_exist_by_name(CString* key, Map* map, Vector* errors, struct SemanticContext* ctx)
{
    struct Variable* has_variable = map_get(map, key);
    return has_variable == NULL;
}

static int analyze_arg_def(struct AstNode* node, Vector* errors, struct SemanticContext* ctx)
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

    int err = 0;
    bool error_occur = false;
    struct Type* type = get_type(type_node, errors, ctx, &error_occur, &err, true);
    if (err != 0) {
        return err;
    }

    if (error_occur == true) {
        return 0;
    }

    struct Variable variable;
    variable_init(&variable, variable_name, type);

    CString key;
    err = cstring_init(&key, variable_name);
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

static int analyze_signature_arguments(struct AstNode* node, Vector* errors, struct SemanticContext* ctx)
{
    if (node == NULL) {
        return 0;
    }
    /*assert(node->type == AST_TYPE_ARG_DEF_LIST);

    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** pointer = vector_get(&node->children, i);
        struct AstNode* arg_def_node = *pointer;
        int err = analyze_arg_def(arg_def_node, errors, ctx);
        if (err != 0) {
            return err;
        }
    }
    
    return 0;*/

    for (size_t i = 0; i < node->children.size; i++) {
        struct AstNode** pointer = vector_get(&node->children, i);
        int err = analyze_arg_def(*pointer, errors, ctx);
        if (err != 0) {
            return err;
        }
    }
    return 0;
}



static struct Type* check_is_variable(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, int *error)
{
    CString variable_name;
    int err = cstring_init(&variable_name, node->text);
    if (err != 0) {
        *error = err;
        return NULL;
    }

    *error_occur = check_variable_not_exist_by_name(&variable_name, &ctx->arguments, errors, ctx);

    // Mean that find varaible
    if (*error_occur == false) {
        struct Variable* variable = map_get(&ctx->arguments, &variable_name);
        cstring_free(&variable_name);
        return variable->type;
    }

    *error_occur = check_variable_not_exist_by_name(&variable_name, &ctx->variables, errors, ctx);

    if (*error_occur == false) {
        struct Variable* variable = map_get(&ctx->variables, &variable_name);
        cstring_free(&variable_name);
        return variable->type;
    }

    struct Error error_info;
    union ErrorData data;
    strcpy(data.text, node->text);
    error_init(&error_info, ERROR_TYPE_VARIABLE_NOT_EXISTS, data);

    err = vector_push(errors, &error);
    if (err != 0) {
        *error = err;
        cstring_free(&variable_name);
        return NULL;
    }

    cstring_free(&variable_name);
    return 0;
}

static struct Type* is_lvalue(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool *error_occur, int* error)
{
    if (node->type == AST_TYPE_IDENTIFIER) {
        return check_is_variable(node, errors, ctx, error_occur, error);
    }

    *error_occur = true;
    struct Error error_info;
    union ErrorData data;
    strcpy(data.text, node->text);
    error_init(&error_info, ERROR_TYPE_NOT_LVALUE, data);
    

    int err = vector_push(errors, &error);
    if (err != 0) {
        *error = err;
        return NULL;
    }

    return NULL;
}

static int analyze_identifier_list(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, struct Type* type)
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

static int analyze_variable_creation(struct AstNode* node, Vector* errors, struct SemanticContext* ctx)
{
    struct AstNode** pointer = vector_get(&node->children, 1);
    struct AstNode* type_node = *pointer;

    bool error_occur = false;

    int err = 0;
    struct Type* type = get_type(type_node, errors, ctx, &error_occur, &err, true);
    if (err != 0) {
        return err;
    }

    if (error_occur == true) {
        return 0;
    }

    pointer = vector_get(&node->children, 0);
    struct AstNode* identifier_list_node = *pointer;

    err = analyze_identifier_list(identifier_list_node, errors, ctx, type);
    if (err != 0) {
        return err;
    }

    //free(type);
    return 0;
}

static int analyze_left_and_right(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, struct ExpressionInfo* left_expr_info, struct ExpressionInfo* right_expr_info)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* left = *pointer;

    int err = analyze_rvalue(left, errors, ctx, error_occur, left_expr_info);
    if (err) {
        return err;
    }

    if (*error_occur == true) {
        return 0;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* right = *pointer;

    err = analyze_rvalue(right, errors, ctx, error_occur, right_expr_info);
    if (err) {
        return err;
    }

    if (*error_occur == true) {
        return 0;
    }
    
    if (types_suitable(left_expr_info->type, right_expr_info->type) == false) {
        struct Error error;
        union ErrorData data = {
            .types = {
                .first_type = left_expr_info->type->kind,
                .second_type = right_expr_info->type->kind,
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

static int analyze_binary_comparing(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, struct ExpressionInfo* expr_info)
{
    struct ExpressionInfo left_info;
    struct ExpressionInfo right_info;
    int err = analyze_left_and_right(node, errors, ctx, error_occur, &left_info, &right_info);
    if (err != 0) {
        return 0;
    }

    if (*error_occur == true) {
        return 0;
    } 

    // No reason to check right type, because types are suitable
    if (type_is_comparable(left_info.type) == false) {
        struct Error error;
        union ErrorData data = {
            .type = left_info.type,
        };
        error_init(&error, ERROR_TYPE_TYPE_NOT_SUPPORT_ORDER, data);
        err = vector_push(errors, &error);
        if (err) {
            return err;
        }
        *error_occur = true;
        return 0;
    }

    expr_info->type = left_info.type;
    expr_info->is_constant = left_info.is_constant && right_info.is_constant;

    return 0;
}

static int analyze_binary_operation(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, struct ExpressionInfo* expr_info, const bool is_boolean_operation)
{
    struct ExpressionInfo left_info;
    struct ExpressionInfo right_info;
    int err = analyze_left_and_right(node, errors, ctx, error_occur, &left_info, &right_info);
    if (err != 0) {
        return 0;
    }

    if (*error_occur == true) {
        return 0;
    } 

    // No reason to check right type, because types are suitable
    if (is_boolean_operation == true && type_support_boolean_operations(left_info.type) == false
        || is_boolean_operation == false && type_support_arithmetic_operations(right_info.type) == false) {
        struct Error error;
        union ErrorData data = {
            .type = left_info.type,
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
    expr_info->is_constant = left_info.is_constant && right_info.is_constant;
   

    if (is_boolean_operation == false) {
        if (left_info.type->kind > right_info.type->kind) {
            expr_info->type = left_info.type;
        } else {
            expr_info->type = right_info.type;
        }
    } else {
        expr_info->type->kind = TYPE_KIND_BOOL;
    }

    // Precomuting constant expressions
    if (expr_info->is_constant == true) {
        if (expr_info->type->kind == TYPE_KIND_INT || expr_info->type->kind == TYPE_KIND_LONG) {
            const int64_t left_value = left_info.value.number;
            const int64_t right_value = right_info.value.number;

            if (node->type == AST_TYPE_PLUS) {
                expr_info->value.number = left_value + right_value;
            } else if (node->type == AST_TYPE_MINUS) {
                expr_info->value.number = left_value - right_value;
            } else if (node->type == AST_TYPE_MUL) {
                expr_info->value.number = left_value * right_value;
            } else if (node->type == AST_TYPE_DIV) {
                expr_info->value.number = left_value / right_value;
            } else {
                assert(0);
            }
 
            expr_info->value.number = left_value + right_value;
        } else if (expr_info->type->kind == TYPE_KIND_UINT || expr_info->type->kind == TYPE_KIND_ULONG) {
            const int64_t left_value = left_info.value.number;
            const int64_t right_value = right_info.value.number;
            
            if (node->type == AST_TYPE_PLUS) {
                expr_info->value.unumber = left_value + right_value;
            } else if (node->type == AST_TYPE_MINUS) {
                expr_info->value.unumber = left_value - right_value;
            } else if (node->type == AST_TYPE_MUL) {
                expr_info->value.unumber = left_value * right_value;
            } else if (node->type == AST_TYPE_DIV) {
                expr_info->value.unumber = left_value / right_value;
            } else {
                assert(0);
            }
        }
    }

    return 0;
}

static int analyze_variable_like_rvalue(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, struct ExpressionInfo* expr_info)
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
    expr_info->is_constant = false;
    expr_info->type = variable->type;

    cstring_free(&name);
    return 0;
}

static bool is_callable(struct AstNode* node) {
    return node->type == AST_TYPE_IDENTIFIER;
}

static int analyze_call_arguments(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, struct Signature* signature)
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

        struct ExpressionInfo info;
        int err = analyze_rvalue(arg, errors, ctx, error_occur, &info);
        if (err) {
            return err;
        }

        if (*error_occur == true) {
            return 0;
        } 

        struct Variable* signature_argument = vector_get(&signature->arguments, i);

        if (types_suitable(info.type, signature_argument->type) == false) {
            struct Error error;
            union ErrorData data = {
                .types.first_type = info.type->kind,
                .types.second_type = signature_argument->type->kind,
            };
            error_init(&error, ERROR_TYPE_INVALID_TYPE, data);

            err = vector_push(errors, &error);

            return err;
        }

    }
    
    return 0;
}

static int analyze_function_call(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, struct ExpressionInfo* expr_info)
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
        expr_info->type = variable->type;
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

        expr_info->type = signature->return_type;
        expr_info->is_constant = false;
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


static int analyze_rvalue(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, bool* error_occur, struct ExpressionInfo* expr_info)
{
    if (node->type == AST_TYPE_DEC) {
        *error_occur = false;
        expr_info->type = malloc(sizeof(struct Type));
        if (expr_info->type == NULL) {
            return -1;
        }
        expr_info->type->kind = TYPE_KIND_INT;
        expr_info->is_constant = true;
        expr_info->value.number = atol(node->text);

        return vector_push(&ctx->types, &expr_info->type);
    } else if (node->type == AST_TYPE_BOOL) {
        *error_occur = false;
        expr_info->type = malloc(sizeof(struct Type));
        if (expr_info->type == NULL) {
            return -1;
        }
        expr_info->type->kind = TYPE_KIND_BOOL;
        expr_info->is_constant = true;
        if (strcmp(node->text, "true") == 0) {
            expr_info->value.boolean = true;
        } else {
            expr_info->value.boolean = false;
        }

        return vector_push(&ctx->types, &expr_info->type);
    } else if (node->type == AST_TYPE_STR) {
        *error_occur = false;
        expr_info->type = malloc(sizeof(struct Type));
        if (expr_info->type == NULL) {
            return -1;
        }
        expr_info->type->kind = TYPE_KIND_STRING;
        expr_info->is_constant = true;

        return vector_push(&ctx->types, &expr_info->type);
    } else if (node->type == AST_TYPE_IDENTIFIER) {
        int err = analyze_variable_like_rvalue(node, errors, ctx, error_occur, expr_info);
        if (err != 0) {
            return err;
        }
    } else if (node->type == AST_TYPE_PLUS || node->type == AST_TYPE_MINUS || node->type == AST_TYPE_MUL || node->type == AST_TYPE_DIV) {
        int err = analyze_binary_operation(node, errors, ctx, error_occur, expr_info, false);
        if (err != 0) {
            return err;
        }
    } else if (node->type == AST_TYPE_OR || node->type == AST_TYPE_AND) {
        int err = analyze_binary_operation(node, errors, ctx, error_occur, expr_info, true);
        if (err != 0) {
            return err;
        }
    } else if (node->type == AST_TYPE_MORE || node->type == AST_TYPE_LESS || node->type == AST_TYPE_EQ || node->type == AST_TYPE_NOT_EQ) {
        int err = analyze_binary_comparing(node, errors, ctx, error_occur, expr_info);
        if (err != 0) {
            return err;
        }
    } else if (node->type == AST_TYPE_CALL_OR_INDEXER) {
        int err = analyze_function_call(node, errors, ctx, error_occur, expr_info);
        if (err != 0) {
            return err;
        }
    } else if (node->type == AST_TYPE_ARRAY) {
        int err = 0;
        struct Type* type = analyze_array_type(node, errors, ctx, error_occur, &err);
        if (err != 0) {
            return err;
        }

        return vector_push(&ctx->types, &type);
    } else {
        assert (0);
    }

    return 0;
}

static int analyze_assigmnet(struct AstNode* node, Vector* errors, struct SemanticContext* ctx)
{
    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* left = *pointer;
    bool error_occur = false;
    int err = 0;
    struct Type *lvalue_type = is_lvalue(left, errors, ctx, &error_occur, &err);
    if (err != 0) {
        return err;
    }
    // No reason to continue analyze assigment
    if (error_occur) {
        return 0;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* right = *pointer;

    struct ExpressionInfo right_info;
    err = analyze_rvalue(right, errors, ctx, &error_occur, &right_info);
    if (err != 0) {
        return err;
    }

    if (error_occur == true) {
        return 0;
    }

    if (types_suitable(lvalue_type, right_info.type) == false) {
        struct Error invalid_type_error;
        union ErrorData data = {
            .types = {
                .first_type = lvalue_type->kind,
                .second_type = right_info.type->kind,
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


static int analyze_cycle_or_if(struct AstNode* node, Vector* errors, struct SemanticContext* ctx, size_t index)
{
    struct AstNode** pointer = vector_get(&node->children, index);
    struct AstNode* expr_node = *pointer;

    bool error_occur = false;
    struct ExpressionInfo info;
    int err = analyze_rvalue(expr_node, errors, ctx, &error_occur, &info);
    if (err != 0) {
        return err;
    }

    if (error_occur == true) {
        return 0;
    }

    if (info.type->kind != TYPE_KIND_BOOL) {
        struct Error invalid_type_error;
        union ErrorData data = {
            .types = {
                .first_type = TYPE_KIND_BOOL,
                .second_type = info.type->kind,
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

static int analyze_do_cycle(struct AstNode* node, Vector* errors, struct SemanticContext* ctx)
{
    ctx->cycle_counter++;
    int res = analyze_cycle_or_if(node, errors, ctx, 2);
    ctx->cycle_counter--;
    return res;
}

static int analyze_while_cycle(struct AstNode* node, Vector* errors, struct SemanticContext* ctx)
{
   ctx->cycle_counter++;
    int res = analyze_cycle_or_if(node, errors, ctx, 0);
    ctx->cycle_counter--;
    return res;
}

static int analyze_if(struct AstNode* node, Vector* errors, struct SemanticContext* ctx)
{
    return analyze_cycle_or_if(node, errors, ctx, 0);
}

static int analyze_break(struct AstNode* node, Vector* errors, struct SemanticContext* ctx)
{
    if (ctx->cycle_counter > 0) {
        return 0;
    }

    struct Error error;
    union ErrorData data;
    error_init(&error, ERROR_TYPE_BREAK_OUTSIDE_OF_CYCLE, data);

    return vector_push(errors, &error);
}

static int analyze_statement(struct AstNode* node, Vector* errors, struct SemanticContext* ctx)
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

static int analyze_statement_list(struct AstNode* node, Vector* errors, struct SemanticContext* ctx)
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

static int semantic_signature_analysis(struct Signature* signature, Vector* errors, struct SemanticContext* ctx)
{
    assert(signature->ast->type == AST_TYPE_FUNC_SIGNATURE);
    struct AstNode **pointer;
    pointer = vector_get(&signature->ast->children, 1);
    struct AstNode* arg_def_list_node = *pointer;
    int err = analyze_signature_arguments(arg_def_list_node, errors, ctx);
    if (err != 0) {
        return err;
    }

    CString function_name;
    err = cstring_init(&function_name, signature->name);
    if (err != 0) {
        return err;
    }

    cstring_free(&function_name);
    return 0;
}

static int semantic_function_analysis(struct Function* function, struct AstNode* node, Vector* errors, struct Program* program)
{   
    assert(node->type == AST_TYPE_FUNC_DEF);

    struct AstNode** pointer = vector_get(&node->children, 0);
    struct AstNode* signature_node = *pointer;

    struct SemanticContext* ctx = malloc(sizeof(struct SemanticContext));
    if (ctx == NULL) {
        return -1;
    }
    function->semantic_context = ctx;

    int err = semantic_analysis_context_init(ctx, program);
    if (err != 0) {
        free(ctx);
        return err;
    }


    err = semantic_signature_analysis(&function->signature, errors, ctx);
    if (err != 0) {
        semantic_analysis_context_free(ctx);
        return err;
    }

    pointer = vector_get(&node->children, 1);
    struct AstNode* statement_list = *pointer;


    err = analyze_statement_list(statement_list, errors, ctx);
    if (err != 0) {
        semantic_analysis_context_free(ctx);
        return err;       
    }

    return 0;
}

static int handle_signature(struct Program* program, struct Signature* signature)
{
    Vector errors;
    const ObjectInfo error_info = {
        .size = sizeof(struct Error),
        .copy = NULL,
        .destructor = NULL,
    };
    int err = vector_init(&errors, error_info);
    if (err != 0) {
        return err;
    }

    struct SemanticContext ctx;
    err = semantic_analysis_context_init(&ctx, program);
    if (err != 0) {
        vector_free(&errors);
        return err;
    }


    err = semantic_signature_analysis(signature, &errors, &ctx);
    if (err != 0) {
        semantic_analysis_context_free(&ctx);
        vector_free(&errors);
        return err;
    }

    if (errors.size != 0) {
        for (size_t j = 0; j < errors.size; j++) {
            struct Error* error = vector_get(&errors, j);
            printf("%s\n", error_to_str(error));
        }
    }

    vector_free(&errors);
    semantic_analysis_context_free(&ctx);

    return 0;
}

static int handle_function(struct Program* program, struct Function* function)
{
    Vector errors;
    const ObjectInfo error_info = {
        .size = sizeof(struct Error),
        .copy = NULL,
        .destructor = NULL,
    };
    int err = vector_init(&errors, error_info);
    if (err != 0) {
        return err;
    }

    err = semantic_function_analysis(function, function->ast, &errors, program);
    if (err != 0) {
        vector_free(&errors);
        return err;
    }

    if (errors.size != 0) {
        for (size_t j = 0; j < errors.size; j++) {
            struct Error* error = vector_get(&errors, j);
            printf("%s\n", error_to_str(error));
        }
    }

    vector_free(&errors);
    return 0;
}

int program_semantic_analysis(struct Program* program)
{
    for (size_t i = 0; i < program->signatures_ptr.capacity; i++) {
        if (program->signatures_ptr.buffer[i].key == NULL) {
            continue;
        }

        struct Signature** pointer = program->signatures_ptr.buffer[i].value;
        struct Signature* signature = *pointer;

        int err = handle_signature(program, signature);
        if (err != 0) {
            return err;
        }
    }

    for (size_t i = 0; i < program->functions_ptr.capacity; i++) {
        if (program->functions_ptr.buffer[i].key == NULL) {
            continue;
        }

        struct Function** pointer = program->functions_ptr.buffer[i].value;
        struct Function* function = *pointer;

        int err = handle_function(program, function);
        if (err != 0) {
            return err;
        }
    }

    return 0;
}
