#include "edlin_parse.h"
#include "edlin_file.h"
#include "edlin_types.h"
#include <ctype.h>
#include <string.h>

#define OFFSET_RST 12
#define OFFSET_A 2
#define EDLIN_CMD_COUNT 16

typedef struct {
    char op_char;
    edlin_token_t token;
    char* help;
} edlin_info_t;

static const edlin_info_t EDLIN_INFO[] = {
    {'?', TOK_HELP,     "Show help                  ?"},
    {'E', TOK_END,      "End (save file)            E"},
    {'Q', TOK_QUIT,     "Quit (throw away changes)  Q"},
    {'A', TOK_APPEND,   "Append                     [#lines]A"},
    {'C', TOK_COPY,     "Copy                       [range],toline[,times]C"},
    {'D', TOK_DELETE,   "Delete                     [range]D Delete lines"},
    {'I', TOK_INSERT,   "Insert                     [line]I"},
    {'L', TOK_LIST,     "List                       [range]L"},
    {'M', TOK_MOVE,     "Move                       [range],tolineM"},
    {'P', TOK_PAGE,     "Page                       [range]P"},
    {'W', TOK_WRITE,    "Write                      [#lines]W"},
    {' ', TOK_EDIT,     "Edit line                  line#"},
    {'R', TOK_REPLACE,  "Replace                    [range][?]R[old],[new]"},
    {'S', TOK_SEARCH,   "Search                     [range][?]S[text]"},
    {'T', TOK_TRANSFER, "Transfer                   [toline]Tfilepath"},
    {'\0', TOK_UNKNOWN, ""}
};

edlin_token_t edlin_tokenize_cmd(char cmd, edlin_size_t start, edlin_size_t end) {
    cmd = toupper(cmd);
    for(edlin_size_t i = start; i < end; ++i) {
        if(EDLIN_INFO[i].op_char == cmd) {
            return EDLIN_INFO[i].token;
        }
    }
    return TOK_UNKNOWN;
}

void edlin_tokenize_args(edlin_cmd_t* cmd, const char* p) {
    // populate the pointers to the arguments

}

void edlin_tokenize(edlin_cmd_t* cmd) {
    edlin_trim_line(&cmd->line);
    const char* start = cmd->line;
    if(*start == '\0') {
        cmd->op = TOK_RETURN;
        return;
    }
    // single character commands with no arguments
    const char* p = strchr(p, '?');
    if(*(p + 1) == '\0') {
        cmd->op = TOK_HELP; // the trimmed string was "?\0"
        return;
    }

}

/*
// figure if Help or optional leading for Replace, Search or Transfer

    char ch = toupper(*(p + 1));
    // check for (R)eplace or (S)earch or (T)ransfer
    if(ch == 'R' || ch == 'S' || ch == 'T') {
        cmd->op = edlin_tokenize_cmd(ch, OFFSET_RST, EDLIN_CMD_COUNT);
        edlin_tokenize_args(cmd, p + 1);
        return;
    }
    cmd->op = TOK_UNKNOWN;
    return;
}
for(edlin_size_t i = OFFSET_A; i < OFFSET_RST; ++i) {
    p = strchr(p, '?');
}
*/
