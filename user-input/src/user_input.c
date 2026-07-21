#include "user_input.h"

#include "colc/cstring.h"
#include "colc/object_info.h"
#include "colc/vector.h"

#include <malloc.h>

int user_input_init(struct UserInput* user_input)
{
    const ObjectInfo flags_info = {
        .size = sizeof(enum Flag),
        .copy = NULL,
        .destructor = NULL,
    };

    int res = vector_init(&user_input->flags, flags_info);
    if (res != 0) {
        return res;
    }

    const ObjectInfo files_info = {
        .size = sizeof(CString),
        .copy = cstring_copy,
        .destructor = cstring_free,
    };

    res = vector_init(&user_input->input_files, files_info);
    if (res != 0) {
        vector_free(&user_input->flags);
        return res;
    }

    return 0;
}

int read_user_input(struct UserInput* user_input, int argc, char** argv)
{
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--ast-graph") == 0) {
            const enum Flag flag = AstGraph;
            int res = vector_push(&user_input->flags, &flag);
            if (res != 0) {
                return res;
            }
        } else if (strncmp(argv[i], "-", 1) == 0) {
            printf("Unknown flag: %s\n", argv[i]);
            return -1;
        } else {
            CString input_file;
            int res = cstring_init(&input_file, argv[i]);
            if (res) {
                return res;
            }
            res = vector_push(&user_input->input_files, &input_file);
            if (res) {
                cstring_free(&input_file);
                return res;
            }
            cstring_free(&input_file);
        }
    }

    return 0;
}

void user_input_free(struct UserInput* user_input)
{
    vector_free(&user_input->input_files);
    vector_free(&user_input->flags);
}

int flag_compare(const void* a, const void* b)
{
    return (enum Flag) a == (enum Flag) b;
}