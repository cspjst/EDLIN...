#include "edlin_parse.h"
#include "edlin_constants.h"
#include "edlin_help.h"
#include "bios_keyboard_services.h"
#include <ctype.h>
#include <stdio.h>

// dispatch table - maps tokens to handler functions
static const edlin_fn_command_t EDLIN_DISPATCH[] = {
    [TOK_EDIT]    = edlin_fn_edit,      // 0
    [TOK_HELP]    = edlin_fn_help,      // 1
    [TOK_END]     = edlin_fn_end,       // 2
    [TOK_QUIT]    = edlin_fn_quit,      // 3
    [TOK_APPEND]  = edlin_fn_append,    // 4
    [TOK_COPY]    = edlin_fn_copy,      // 5
    [TOK_DELETE]  = edlin_fn_delete,    // 6
    [TOK_INSERT]  = edlin_fn_insert,    // 7
    [TOK_LIST]    = edlin_fn_list,      // 8
    [TOK_MOVE]    = edlin_fn_move,      // 9
    [TOK_PAGE]    = edlin_fn_page,      // 10
    [TOK_WRITE]   = edlin_fn_write,     // 11
    [TOK_REPLACE] = edlin_fn_replace,   // 12
    [TOK_SEARCH]  = edlin_fn_search,    // 13
    [TOK_TRANSFER] = edlin_fn_transfer, // 14
    [TOK_ERROR]   = edlin_fn_error,     // 15
    [TOK_EMPTY]   = edlin_fn_empty,     // 16
    [TOK_UNKNOWN] = edlin_fn_unknown    // 17
};

bool edlin_parse(edlin_cmd_t* cmd, edlin_file_t* file) {
    edlin_fn_command_t fn = EDLIN_DISPATCH[cmd->token];
    return fn(cmd, file);
}

bool edlin_fn_edit(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_help(edlin_cmd_t* cmd, edlin_file_t* file) {
    for(int i = 0; i < EDLIN_CMD_COUNT; ++i) {
        printf("%s\n", EDLIN_HELP[i]);
    }
    return true;
}

bool edlin_fn_end(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_quit(edlin_cmd_t* cmd, edlin_file_t* file) {
    return !wait_yesno("Abort edit");
}

bool edlin_fn_append(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_copy(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_delete(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_insert(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_list(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_move(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_page(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_write(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_replace(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_search(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_transfer(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_error(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_empty(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}

bool edlin_fn_unknown(edlin_cmd_t* cmd, edlin_file_t* file) {
    return false;
}
