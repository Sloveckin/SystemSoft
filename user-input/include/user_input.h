#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "colc/vector.h"

enum Flag {
    AstGraph,
    Log
};

struct UserInput {
    Vector input_files;
    Vector flags;
    bool print_log;
    bool write_cfg;
};

int flag_compare(const void* a, const void* b);

int user_input_init(struct UserInput* user_input);

int read_user_input(struct UserInput* user_input, int argc, char** argv);

void user_input_free(struct UserInput* user_input);

#endif