#include "edlin_tokenize.h"
#include "edlin_file.h"
#include <ctype.h>
#include <string.h>

#define OFFSET_A 4
#define OFFSET_RST 12
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
    {'C', TOK_COPY,     "Copy                       [range][,times]C"},
    {'D', TOK_DELETE,   "Delete                     [range]D Delete lines"},
    {'I', TOK_INSERT,   "Insert                     [line]I"},
    {'L', TOK_LIST,     "List                       [range]L"},
    {'M', TOK_MOVE,     "Move                       [range],tolineM"},
    {'P', TOK_PAGE,     "Page                       [range]P"},
    {'W', TOK_WRITE,    "Write                      [#lines]W"},
    {'R', TOK_REPLACE,  "Replace                    [range][?]R[old],[new]"},
    {'S', TOK_SEARCH,   "Search                     [range][?]S[text]"},
    {'T', TOK_TRANSFER, "Transfer                   [toline]Tfilepath"},
    {' ', TOK_ERROR,    "Command syntax error!"},
    {' ', TOK_EMPTY,    "Empty input!"},
    {' ', TOK_UNKNOWN, "Unknown command!"}
};

char* edlin_help(edlin_size_t i) {
    return EDLIN_INFO[i].help;
}

bool is_tokenize_empty(edlin_cmd_t* cmd, char* p) {
    if(*p == '\0') {
        cmd->op = TOK_EMPTY;
        return true;
    }
    return false;
}

bool is_tokenize_EQ(edlin_cmd_t* cmd, char* p) {
    for(int i = 1; i < OFFSET_A; ++i) { // ?, E, Q search window
        if(toupper(*p) == EDLIN_INFO[i].op_char) {
            if(*(p + 1) != '\0') {
                cmd->op = TOK_ERROR;
                return true; // trailing arg syntax error
            }
            cmd->op = EDLIN_INFO[i].token;
            return true;
        }
    }
    return false;
}

bool is_tokenize_ACDILMPW(edlin_cmd_t* cmd, char* p, char* start) {
    for(int i = OFFSET_A; i < OFFSET_RST; ++i) {
        if(toupper(*p) == EDLIN_INFO[i].op_char) {
            if(*(p + 1) != '\0') {
                cmd->op = TOK_ERROR;
                return true; // trailing arg syntax error
            }
            cmd->op = EDLIN_INFO[i].token;
            *p = '\0';  // shorten the string to its args
            int j = 0;
            // tokenize leading args
            if(*start == ',') { // check for current line syntax
                cmd->argv[j++] = start;
            }
            p = strtok(start, ",");
            while (p != NULL && j < EDLIN_ARGC_MAX - 1) {
                cmd->argv[j++] = p;  // Store pointer to arg
                p = strtok(NULL, ",");    // Get next token
            }
            cmd->argc = j;
            return true;
        }
    }
    return false;
}

bool is_tokenize_RST(edlin_cmd_t* cmd, char* p, char* start) {
    for(int i = OFFSET_RST; i < EDLIN_CMD_COUNT; ++i) {
        if(toupper(*p) == EDLIN_INFO[i].op_char) {
            cmd->op = EDLIN_INFO[i].token;
            *p = '\0';  // split string leading, trailing args
            char* split = p + 1;
            // Check for interactive modifier '?' before the command char
             int j = 0;
            if(*(p - 1) == '?') {
                *(p - 1) = '\0'; // Null-terminate before '?'
                cmd->argv[j++] = "?"; // interactive
            } else {
                cmd->argv[j++] = "!"; // non-interactive
            }
            // tokenize leading args
            if(*start == ',') { // check for current line syntax
                cmd->argv[j++] = start;
            }
            p = strtok(start, ",");
            while (p != NULL && j < EDLIN_ARGC_MAX) {
                cmd->argv[j++] = p;  // Store pointer to arg
                p = strtok(NULL, ",");    // Get next token
            }
            // tokenize trailing args
            p = strtok(split, ",");
            while (p != NULL && j < EDLIN_ARGC_MAX) {
                cmd->argv[j++] = p;  // Store pointer to arg
                p = strtok(NULL, ",");    // Get next token
            }
            cmd->argc = j;
            return true;
        }
    }
    return false;
}

void do_tokenize_digits(edlin_cmd_t* cmd, char* p) {
    while(*p != '\0') {
        if(!isdigit(*p)) {
            cmd->op = TOK_ERROR;
            return; // syntax error
        }
        p++;
    }
    cmd->op = TOK_EDIT;
    cmd->argc = 1;
    cmd->argv[0] = cmd->line;
}

void edlin_tokenize(edlin_cmd_t* cmd) {
    edlin_trim_line(&cmd->line);
    char* start = cmd->line;
    char* end = start + strlen(cmd->line);
    char* p = start;
    cmd->argc = 0;
    memset(cmd->argv, 0, sizeof(cmd->argv)); // set all pointers to NULL
    // 1. check if just hit enter
    if(is_tokenize_empty(cmd, p)) {
        return;
    }
    // 2. single character commands with no arguments
    if(is_tokenize_EQ(cmd, p)) {
        return;
    }
    // 3. single character commands with arguments
    while(*p != '\0') {
        if(!isalpha(*p)) {
           p++;
           continue;
        }
        // 3.1 leading args
        if(is_tokenize_ACDILMPW(cmd, p, start)) {
            return;
        }
        // 3.2 leading and trailing args
        if(is_tokenize_RST(cmd, p, start)) {
            return;
        }
        p++;
    }
    // 4. its all numbers or syntax error
    do_tokenize_digits(cmd, start);
}
