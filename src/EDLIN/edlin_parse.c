#include "edlin_parse.h" 

// dispatch table - maps tokens to handler functions
static const edlin_command_handler_t EDLIN_DISPATCH[] = {
    [TOK_EDIT]    = edlin_handle_edit,      // 0
    [TOK_HELP]    = edlin_handle_help,      // 1
    [TOK_END]     = edlin_handle_end,       // 2
    [TOK_QUIT]    = edlin_handle_quit,      // 3
    [TOK_APPEND]  = edlin_handle_append,    // 4
    [TOK_COPY]    = edlin_handle_copy,      // 5
    [TOK_DELETE]  = edlin_handle_delete,    // 6
    [TOK_INSERT]  = edlin_handle_insert,    // 7
    [TOK_LIST]    = edlin_handle_list,      // 8
    [TOK_MOVE]    = edlin_handle_move,      // 9
    [TOK_PAGE]    = edlin_handle_page,      // 10
    [TOK_WRITE]   = edlin_handle_write,     // 11
    [TOK_REPLACE] = edlin_handle_replace,   // 12
    [TOK_SEARCH]  = edlin_handle_search,    // 13
    [TOK_TRANSFER] = edlin_handle_transfer, // 14
    [TOK_ERROR]   = edlin_handle_error,     // 15
    [TOK_EMPTY]   = edlin_handle_empty,     // 16
    [TOK_UNKNOWN] = edlin_handle_unknown    // 17
};

#define DISPATCH_TABLE_SIZE (sizeof(command_table) / sizeof(command_table[0]))

bool edlin_dispatch_command(edlin_cmd_t* cmd, edlin_file_t* file) {
    edlin_command_handler_t fn = EDLIN_DISPATCH[cmd->token];
    return fn(cmd, file);
}

