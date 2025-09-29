#include "edlin_tokenize.h"
#include "edlin_constants.h"
#include "edlin_types.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define OFFSET_RST 7

static const edlin_token_t EDLIN_TOKENS[] = {
    {'A', TOK_APPEND},   // Append                     [#lines]A
    {'C', TOK_COPY},     // Copy                       [range][,times]C
    {'D', TOK_DELETE},   // Delete                     [range]D Delete lines
    {'I', TOK_INSERT},   // Insert                     [line]I
    {'L', TOK_LIST},     // List                       [range]L
    {'M', TOK_MOVE},     // Move                       [range],tolineM
    {'P', TOK_PAGE},     // Page                       [range]P
    {'W', TOK_WRITE},    // Write                      [#lines]W
    {'R', TOK_REPLACE},  // Replace                    [range][?]R[old],[new]
    {'S', TOK_SEARCH},   // Search                     [range][?]S[text]
    {'T', TOK_TRANSFER}, // Transfer                   [toline]Tfilepath
};

static const char EDLIN_QUERY[] = "?";

char* tokenize_args(edlin_cmd_t* cmd, char* p) {
    char* begin = p;
    while(!isalpha(*p) && *p != ';') p++;
    for(int i = 0; i < OFFSET_RST; ++i) {
        if(toupper(*p) == EDLIN_TOKENS[i].ascii) {
            cmd->token = EDLIN_TOKENS[i].token;
            *p = '\0';  // shorten the string to its args
            int j = 0;
            // tokenize CSV list of args
            if(*origin == ',') { // check for current line syntax
                cmd->argv[j++] = begin;
            }
            char * parg = strtok(origin, ",");
            while (csv != NULL && j < EDLIN_ARGC_MAX - 1) {
                cmd->argv[j++] = parg;  // Store pointer to arg
                parg = strtok(NULL, ",");    // Get next token
            }
            cmd->argc = j;
            return p;
        }
    }
    return begin;
}

char* tokenize_no_args(edlin_cmd_t* cmd, char* p) {
    while(isspace(*p) || *p == ',' || *p == ';') p++;
    switch(*p) {
    case'?':
        cmd->token = TOK_HELP;
        return p;
    case'e':
    case'E':
        cmd->token = TOK_END;
        return p;
    case'q':
    case'Q':
        cmd->token = TOK_QUIT;
        return p;
    default:
        return p;
    }
}

char* tokenize_edit(edlin_cmd_t* cmd, char* p) {
    if(!isdigit(*p) && *p != '.') return p;
    cmd->token = TOK_EDIT;
    cmd->argc = 1;
    cmd->argv[0] = p;
    while(isdigit(*p)) p++;
    if(*p == ';' || *p == '\n') *p = '\0';
    else cmd->token = TOK_ERROR;
    return p;
}

char* tokenize_empty(edlin_cmd_t* cmd, char* p) {
    while(isspace(*p)) p++;
    if(!strlen(p)) {
        cmd->token = TOK_EMPTY;
        return p;
    }
    return p;
}

char* edlin_tokenize(edlin_cmd_t* cmd, char* input) {
    char* p = input;
    memset(cmd, 0, sizeof(edlin_cmd_t));
    p = tokenize_empty(cmd, p);
    if(cmd->token) return p;
    p = tokenize_args(cmd, p);
    if(cmd->token) return p;
    p = tokenize_no_args(cmd, p);
    if(cmd->token) return p;
    return tokenize_edit(cmd, p);
}

// 1. set all pointers to NULL

// 2. single character commands with arguments
/*
while(*p != 0) {
    if(!isalpha(*p)) {
        p++;
        continue;
    }
    // 2.1 leading args
    if(is_tokenize_args(cmd, p, cmd->line)) return;
    // 2.2 leading and trailing args
    if(is_tokenize_query(cmd, p, cmd->line)) return;
    p++;
}
*/
// 3. single character commands with no arguments
//if(is_tokenize_no_args(cmd, p)) return;
// 4. digits or syntax error
//

/*
if(*p == '?')  {
    cmd->token = TOK_HELP;
    return p;
}
for(int i = 0; i < OFFSET_A; ++i) {
    if(toupper(*p) == EDLIN_TOKENS[i].ascii) {
        cmd->token = EDLIN_TOKENS[i].token;
        return p;
    }
}
 */
