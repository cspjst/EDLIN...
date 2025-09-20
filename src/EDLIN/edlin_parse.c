#include "edlin_parse.h"
#include "edlin_types.h"
#include <ctype.h>

typedef struct {
    char op_char;
    edlin_token_t token;
    char* help;
} edlin_info_t;

static const edlin_info_t EDLIN_INFO[] = {
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

edlin_token_t edlin_cmd_token(char op_char) {
    op_char = toupper(op_char);
    for(edlin_size_t i = 0; i < 4; ++i) {//EDLIN_OP_COUNT; ++i) {
        if(EDLIN_INFO[i].op_char == op_char) {
            printf("%s\n", EDLIN_INFO[i].help);
            return EDLIN_INFO[i].token;
        }
    }
    return TOK_UNKNOWN;
}

bool edlin_tokenize(edlin_cmd_t* cmd) {
    return false;
}
