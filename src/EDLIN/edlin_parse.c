#include "edlin_parse.h"
#include "edlin_file.h"
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
    {' ', TOK_EDIT,     "Edit line                  line#"},
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
    {'R', TOK_REPLACE,  "Replace                    [range][?]R[old],[new]"},
    {'S', TOK_SEARCH,   "Search                     [range][?]S[text]"},
    {'T', TOK_TRANSFER, "Transfer                   [toline]Tfilepath"},
    {'\0', TOK_UNKNOWN, ""}
};

void edlin_tokenize(edlin_cmd_t* cmd) {
    edlin_trim_line(&cmd->line);
    char* start = cmd->line;
    char* p = start;
    // 1. check if just hit enter
    if(*p == '\0') {
        cmd->op = TOK_RETURN;
        return;
    }
    // 2. single character commands with no arguments
    for(int i = 1; i < OFFSET_A; ++i) { // search window
        if(toupper(*p) == EDLIN_INFO[i].op_char) {
            *******************
            if(*(p + 1) != '\0') {
                cmd->op = TOK_ERROR;
            }
            // "?\0", "E\0", or "Q\0"
            cmd->op = EDLIN_INFO[i].token;
            return;
        }
    }
    // 3. single character commands with only leading arguments
    for(int i = OFFSET_A; i < OFFSET_RST; ++i) {
        // A, C, D, I, L, M, P, or W
        if(toupper(*p) == EDLIN_INFO[i].op_char) {
            if(*(p + 1) != '\0') {
                cmd->op = TOK_ERROR;
            }
            cmd->op = EDLIN_INFO[i].token;
            *p = '\0';  // shorten the string to its args
            int j = 0;
            p = strtok(start, ",");
            while (p != NULL && j < EDLIN_FIELDS_MAX) {
                cmd->fields[j++] = p;  // Store pointer to arg
                p = strtok(NULL, ",");    // Get next token
            }
            return;
        }
    }
    // 4. single character commands with leading and trailing arguments
    for(int i = OFFSET_RST; i < EDLIN_CMD_COUNT; ++i) {
        // R, S, or T
        if(toupper(*p) == EDLIN_INFO[i].op_char) {
            cmd->op = EDLIN_INFO[i].token;
            *p = '\0';  // split string leading, trailing args
            char* split = p;
            // leading tokens
            int j = 0;
            p = strtok(start, ",");
            while (p != NULL && j < EDLIN_FIELDS_MAX) {
                cmd->fields[j++] = p;  // Store pointer to arg
                p = strtok(NULL, ",");    // Get next token
            }
            // trailing tokens
            p = strtok(split, ",");
            while (p != NULL && j < EDLIN_FIELDS_MAX) {
                cmd->fields[j++] = p;  // Store pointer to arg
                p = strtok(NULL, ",");    // Get next token
            }
            return;
        }
    }
    cmd->op = TOK_UNKNOWN;
}
