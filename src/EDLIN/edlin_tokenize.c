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
    char* begin = p;                                // copy of start of input
    while(!isalpha(*p) && *p != ';') p++;           // scan over until candidate char
    for(int i = 0; i < OFFSET_RST; ++i) {           // search the char table
        if(toupper(*p) == EDLIN_TOKENS[i].ascii) {  // valid comand char  
            cmd->token = EDLIN_TOKENS[i].token;     // tokenize
            *p = '\0';                              // replace with end args
            int j = 0;                              // j arg counter  
            // tokenize CSV list of args
            if(*origin == ',') {                    // check for current line syntax
                cmd->argv[j++] = begin;             // store pointer to arg
            }
            char * parg = strtok(origin, ",");      // tokenize by CSV  
            while (csv != NULL && j < EDLIN_ARGC_MAX - 1) {
                cmd->argv[j++] = parg;              // store pointer to arg
                parg = strtok(NULL, ",");           // get next token
            }
            cmd->argc = j;                          // store argc  
            return p;                               // update input ptr  
        }
    }
    return begin;                                   // next filter  
}

char* tokenize_no_args(edlin_cmd_t* cmd, char* p) {
    // scan until candidate char
    while(isspace(*p) || *p == ',' || *p == ';') p++;
    switch(*p) {                 // handle valid no arg commands
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
        return p;                // no valid chars
    }
}

char* tokenize_edit(edlin_cmd_t* cmd, char* p) {
    if(!isdigit(*p) && *p != '.') return p;   // scan over invalid chars
    cmd->token = TOK_EDIT;                    // found a number    
    cmd->argc = 1;                            // 1 arg
    cmd->argv[0] = p;                         // set ptr to arg
    while(isdigit(*p)) p++;                   // scan until no more digits 
    if(*p == ';' || *p == '\n') *p = '\0';    // end the arg data
    else cmd->token = TOK_ERROR;              // syntax error
    return p;                                 
}

char* tokenize_empty(edlin_cmd_t* cmd, char* p) {
    while(isspace(*p)) p++;                // scan over whitespace
    if(!strlen(p)) {                       // empty input string
        cmd->token = TOK_EMPTY;            // tokenize
        return p;
    }
    return p;                              // next filter
}

char* edlin_tokenize(edlin_cmd_t* cmd, char* input) {
    char* p = input;                        // series of fall through filters
    memset(cmd, 0, sizeof(edlin_cmd_t));    // zero out the cmd struct
    p = tokenize_empty(cmd, p);             // empty line?
    if(cmd->token) return p;                // yes
    p = tokenize_args(cmd, p);              // A,D,I,L,M,P,W ?
    if(cmd->token) return p;                // yes
    p = tokenize_no_args(cmd, p);           // ?,E,Q 
    if(cmd->token) return p;                // yes
    return tokenize_edit(cmd, p);           // line edit or error
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
