#include "backend/common/function.h"

#include "backend/cfg/control_flow_graph_node.h"
#include "backend/common/signature.h"
#include "backend/error/error.h"
#include "backend/semantic_analysis/semantic_analysis.h"
#include "colc/object_info.h"
#include "colc/vector.h"

#include <malloc.h>
#include <string.h>
#include <assert.h>

int function_init(struct Function* function, struct AstNode *node, struct Signature* signature)
{
    /*struct Signature* signature = malloc(sizeof(struct Signature));
    if (signature == NULL) {
        return -1;
    }
    struct AstNode** signature_node = vector_get(&node->children, 0);
    assert(*signature_node);
    int res = signature_init(signature, *signature_node);
    if (res != 0) {
        free(signature);
        return res;
    }*/
    function->signature = signature;

    struct AstNode** statement_list = vector_get(&node->children, 1);
    if (*statement_list == NULL) {
        function->cfg = NULL;
        return 0;
    }

    

    function->cfg = create_control_flow_graph(*statement_list);
    if (function->cfg == NULL) {
        free(signature);
        return -1;
    }
    
    return 0;
}

void function_free(struct Function* function)
{
    //signature_free(function->signature);
    free(function->signature);
    if (function->cfg != NULL) {
        control_graph_free(function->cfg);
    }
}