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

char* tokenize_post_args (edlin_cmd_t* cmd, char* p) {
    char* p0 = p;                                   // copy of start of input
    while(!isalpha(*p)) p++;                        // scan over until candidate char
    for(int i = OFFSET_RST; i < EDLIN_CMD_COUNT; ++i) {
        if(*p == '?') cmd->argv[j++] = p++;         // interactive
        if(toupper(*p) == EDLIN_TOKENS[i].ascii) {
            int j = 0;                               // j arg counter
            cmd->token = EDLIN_TOKENS[i].token;
            if(p == p0) p0++;                       // replace with end args
            else *p = ',';                          // replace so CSV pre and post
            if(*(p - 1) == '?') cmd->argv[j++] = p -1    // interactive query mode 
            // tokenize CSV list of args
            if(*p0 == ',') {                        // check for current line syntax
                cmd->argv[j++] = p0++;              // store pointer to arg
            }
            char * arg = strtok(p0, ",\x1A");     // tokenize by CSV, CTRL-Z
            while (arg != NULL && j < EDLIN_ARGC_MAX) {
                cmd->argv[j++] = arg;               // store pointer to arg
                arg = strtok(NULL, ",\x1A");      // get next token
            }
            cmd->argc = j;                          // store argc
            while(*p != '\x1A' && *p != '\n') p++;  // scan to ctrl-z or \n
            return p;                               // update input ptr
        }
    }
    return p0;
}

char* tokenize_pre_args(edlin_cmd_t* cmd, char* p) {
    char* p0 = p;                                   // copy of start of input
    while(!isalpha(*p)) p++;                        // scan over until candidate char
    for(int i = 0; i < OFFSET_RST; ++i) {           // search the char table
        if(toupper(*p) == EDLIN_TOKENS[i].ascii) {  // valid comand char
            int j = 0;                              // j arg counter
            cmd->token = EDLIN_TOKENS[i].token;     // tokenize
            *p = '\0';                              // replace with end args
            // tokenize CSV list of args
            if(*p0 == ',') {                        // check for current line syntax
                cmd->argv[j++] = p0++;              // store pointer to arg
            }
            char * arg = strtok(p0, ",");           // tokenize by CSV
            while (arg != NULL && j < EDLIN_ARGC_MAX) {
                cmd->argv[j++] = arg;               // store pointer to arg
                arg = strtok(NULL, ",");            // get next token
            }
            cmd->argc = j;                          // store argc
            return p;                               // update input ptr
        }
    }
    return p0;                                      // next filter
}

char* tokenize_no_args(edlin_cmd_t* cmd, char* p) {
    while(isspace(*p) || *p == ',' || *p == ';') p++;
    switch(*p) {                                    // handle valid no arg commands
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
        return p;                                   // no valid chars
    }
}

char* tokenize_edit(edlin_cmd_t* cmd, char* p) {
    if(!isdigit(*p) && *p != '.') return p;         // invalid chars
    cmd->token = TOK_EDIT;                          // found a digit
    cmd->argc = 1;                                  // 1 arg
    cmd->argv[0] = p;                               // store ptr to arg
    while(isdigit(*p)) p++;                         // scan until no more digits
    if(*p == ';' || *p == '\n') *p = '\0';          // end the arg data
    else cmd->token = TOK_ERROR;                    // otherwise syntax error
    return p;                                       // success
}

char* edlin_tokenize(edlin_cmd_t* cmd, char* input) {
    char* p = input;                                // series of fall through filters
    memset(cmd, 0, sizeof(edlin_cmd_t));            // zero out the cmd struct
    while(isspace(*p)) p++;                         // scan over any whitespace
    if(!strlen(p)) cmd->token = TOK_EMPTY;          // empty input string ?
    if(cmd->token) return p;                        // yes
    p = tokenize_post_args(cmd, p);                 // ?R,?S,T
    if(cmd->token) return p;                        // yes
    p = tokenize_pre_args(cmd, p);                  // A,D,I,L,M,P,W
    if(cmd->token) return p;                        // yes
    p = tokenize_no_args(cmd, p);                   // ?,E,Q
    if(cmd->token) return p;                        // yes
    return tokenize_edit(cmd, p);                   // line edit or error
}
