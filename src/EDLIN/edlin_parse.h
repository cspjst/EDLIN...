#ifndef EDLIN_PARSE_H
#define EDLIN_PARSE_H

#include "edlin_types.h"
#include <stdbool.h>

// function signature for dispatch table
typedef bool (*edlin_command_handler_t)(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_command_dispatcher(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_edit(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_help(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_end(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_quit(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_append(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_copy(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_delete(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_insert(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_list(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_move(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_page(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_write(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_replace(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_search(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_transfer(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_error(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_empty(edlin_cmd_t* cmd, edlin_file_t* file);

bool edlin_handle_unknown(edlin_cmd_t* cmd, edlin_file_t* file);

#endif
