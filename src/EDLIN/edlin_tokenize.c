#include "edlin_tokenize.h"
#include "edlin_types.h"
#include <ctype.h>
#include <string.h>

#include <stdio.h>

#define OFFSET_A 6
#define OFFSET_RST 14
#define EDLIN_CMD_COUNT 18

typedef struct {
    char ascii;
    edlin_token_t token;
    char* help;
} edlin_info_t;

static const edlin_info_t EDLIN_INFO[] = {
    {' ', TOK_EDIT,     "Edit line                  line#"},
    {'#', TOK_HASH,     "Line after the last line   #"},
    {'.', TOK_DOT,      "Current edit line          ."},
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

static const char EDLIN_QUERY[] = "?";

char* edlin_help(edlin_size_t i) {
    return EDLIN_INFO[i].help;
}

bool is_tokenize_no_args(edlin_cmd_t* cmd, char* p) {
    cmd->token = TOK_ERROR;
    for(int i = 0; i < OFFSET_A; ++i) {
        if(toupper(*p) == EDLIN_INFO[i].ascii) {
            if(*(p + 1) != '\0') return true; // trailing arg syntax error
            cmd->token = EDLIN_INFO[i].token;
            return true;
        }
    }
    return false;
}

bool is_tokenize_args(edlin_cmd_t* cmd, char* p, char* start) {
    cmd->token = TOK_ERROR;
    for(int i = OFFSET_A; i < OFFSET_RST; ++i) {
        if(toupper(*p) == EDLIN_INFO[i].ascii) {
            if(*(p + 1) != '\0') return true; // trailing arg syntax error
            cmd->token = EDLIN_INFO[i].token;
            *p = '\0';  // shorten the string to its args
            int j = 0;
            // tokenize CSV list of args
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

bool is_tokenize_query(edlin_cmd_t* cmd, char* p, char* start) {
    for(int i = OFFSET_RST; i < EDLIN_CMD_COUNT; ++i) {
        if(toupper(*p) == EDLIN_INFO[i].ascii) {
            cmd->token = EDLIN_INFO[i].token;
            *p = ',';  // replace so CSV
            char* split = p + 1;
            // 1. Check for interactive modifier '?' before the command char
            int j = 0;
            if(*(p - 1) == '?') {
                *(p - 1) = ','; // replace so CSV
                cmd->argv[j++] = EDLIN_QUERY; // interactive
            } else {
                cmd->argv[j++] = p; // non-interactive
            }
            // 2. tokenize CSV list of args
            if(*start == ',') { // check for current line syntax
                cmd->argv[j++] = start;
            }
            p = strtok(start, ",");
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
    cmd->token = TOK_ERROR;
    while(*p != '\0') {
        if(!isdigit(*p)) return; // syntax error
        p++;
    }
    cmd->token = TOK_EDIT;
    cmd->argc = 1;
    cmd->argv[0] = cmd->line;
}

void edlin_tokenize(edlin_cmd_t* cmd) {
    char* p = cmd->line;
    cmd->argc = 0;
    // 1. set all pointers to NULL
    memset(cmd->argv, 0, sizeof(cmd->argv));
    // 2. single character commands with no arguments
    if(is_tokenize_no_args(cmd, p)) return;
    // 3. single character commands with arguments
    while(*p != 0) {
        if(!isalpha(*p)) {
            p++;
            continue;
        }
        // 3.1 leading args
        if(is_tokenize_args(cmd, p, cmd->line)) return;
        // 3.2 leading and trailing args
        if(is_tokenize_query(cmd, p, cmd->line)) return;
        p++;
    }
    // 4. digits or syntax error
    do_tokenize_digits(cmd, cmd->line);
}
