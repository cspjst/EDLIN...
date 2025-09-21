#include "edlin_parse.h"
#include "edlin_types.h"
#include <ctype.h>

typedef struct {
    char op_char;
    edlin_token_t token;
    char* help;
} edlin_info_t;

static const edlin_info_t EDLIN_INFO[] = {
    {'\0', TOK_UNKNOWN, ""},
    {'-', TOK_EDIT,     "Edit line                  line#"},
    {'?', TOK_HELP,     "Show help                  ?"},
    {'A', TOK_APPEND,   "Append                     [#lines]A"},
    {'C', TOK_COPY,     "Copy                       [range],toline[,times]C"},
    {'D', TOK_DELETE,   "Delete                     [range]D Delete lines"},
    {'E', TOK_END,      "End (save file)            E"},
    {'I', TOK_INSERT,   "Insert                     [line]I"},
    {'L', TOK_LIST,     "List                       [range]L"},
    {'M', TOK_MOVE,     "Move                       [range],tolineM"},
    {'P', TOK_PAGE,     "Page                       [range]P"},
    {'Q', TOK_QUIT,     "Quit (throw away changes)  Q"},
    {'R', TOK_REPLACE,  "Replace                    [range][?]R[old],[new]"},
    {'S', TOK_SEARCH,   "Search                     [range][?]S[text]"},
    {'T', TOK_TRANSFER, "Transfer                   [toline]Tfilepath"},
    {'W', TOK_WRITE,    "Write                      [#lines]W"}
};

edlin_token_t edlin_cmd_token(char cmd_char) {
    cmd_char = toupper(cmd_char);
    for(edlin_size_t i = 1; i < EDLIN_CMD_COUNT; ++i) {
        if(EDLIN_INFO[i].op_char == cmd_char) {
            return EDLIN_INFO[i].token;
        }
    }
    return TOK_UNKNOWN;
}

char edlin_find_cmd_char(edlin_cmd_t* cmd) {

}

bool edlin_tokenize(edlin_cmd_t* cmd) {
    return false;
}
