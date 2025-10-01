#include "edlin_tokenize.h"
#include "edlin_constants.h"
#include "edlin_types.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

static const edlin_token_t EDLIN_TOKENS[] = {
    {'?', TOK_HELP},     // Show help   ?
    {'E', TOK_END},      // End         E (save file)
    {'Q', TOK_QUIT},     // Quit        Q (throw away changes)
    {'A', TOK_APPEND},   // Append      [#lines]A
    {'C', TOK_COPY},     // Copy        [range][,times]C
    {'D', TOK_DELETE},   // Delete      [range]D Delete lines
    {'I', TOK_INSERT},   // Insert      [line]I
    {'L', TOK_LIST},     // List        [range]L
    {'M', TOK_MOVE},     // Move        [range],tolineM
    {'P', TOK_PAGE},     // Page        [range]P
    {'W', TOK_WRITE},    // Write       [#lines]W
    {'R', TOK_REPLACE},  // Replace     [range][?]R[old],[new]
    {'S', TOK_SEARCH},   // Search      [range][?]S[text]
    {'T', TOK_TRANSFER} // Transfer    [toline]Tfilepath
};



void edlin_inplace_tokenize(char *p) {
    while(*p) {
        if(*p == '?') {
            *p++ = TOK_QUERY;                       // assume interactive
            switch(toupper(*p)) {
            case'R':
                *p = TOK_REPLACE;
                while(*p && *p != '\x1A') p++;      // skip past replace args
                continue;
            case'S':
                *p = TOK_SEARCH;
                while(*p && *p != '\x1a') p++;      // skip past search arg
                if(*p == '\x1a') p++;
                continue;
            default:
                *(p - 1) = TOK_HELP;
                continue;
            }
        }
        for(int i = 1; i < 13; ++i) {

        }
        p++;
    }
}

char* edlin_tokenize_QSR(edlin_cmd_t* cmd, char* input) {
    char* p = input;
    while(*p  != '\0') {
        if(*p == '?') {
            p++;
            switch(toupper(*p)) {
            case'R':
                cmd->token = TOK_QREPLACE;
                return collect pre post args(p);
            case'S':
                cmd->token = TOK_QSEARCH;
                 return collect pre post args(p);
            default:
                cmd->token = TOK_HELP;
                return p;
            }
        }
    }
}

char* edlin_tokenize(edlin_cmd_t* cmd, char* input) {
    char* p = input;                                // series of fall through filters
    memset(cmd, 0, sizeof(edlin_cmd_t));            // zero out the cmd struct
    while(isspace(*p)) p++;                         // scan over any whitespace
    if(*p == '\0') {                                // empty input string ?
        cmd->token = TOK_EMPTY;          
        return p;    
    }
    p[strcspn(p, "\n")] = '\0';                     // trim \n
    if(edlin_tokenize_QSR(cmd, p)) return p;        // search or replace ?
    
    return p;
}


/*
char* tokenize_post_args (edlin_cmd_t* cmd, char* p) {
    char* p0 = p;                                   // copy of start of input
    while(!isalpha(*p)) p++;           // scan over until candidate char
    if(*p == ';') return p0;
    for(int i = 8; i < 11; ++i) { // R,S,T search
        if(toupper(*p) == EDLIN_TOKENS[i].ascii) {
            int j = 0;                              // j arg counter
            cmd->token = EDLIN_TOKENS[i].token;     // tokenize
            *p = '\0';                              // replace with end args
            if(p0 < p) { // has pre args
                if(*(p - 1) == '?')  cmd->query = true;
                // tokenize CSV list of pre args
                if(*p0 == ',') {                        // check for current line syntax
                    cmd->argv[j++] = p0++;              // store pointer to arg
                }
                char * arg = strtok(p0, ",?");       // tokenize by CSV, CTRL-Z
                while (arg != NULL && j < EDLIN_ARGC_MAX) {
                    cmd->argv[j++] = arg;               // store pointer to arg
                    arg = strtok(NULL, ",?");        // get next token
                }
            }
            // tokenize CSV list of post args
            char * arg = strtok(++p, ",\x1A\n");       // tokenize by CSV, CTRL-Z
            while (arg != NULL && j < EDLIN_ARGC_MAX) {
                cmd->argv[j++] = arg;               // store pointer to arg
                arg = strtok(NULL, ",\x1A\n");        // get next token
            }
            cmd->argc = j;                          // store argc
            while(*p != '\0' && *p != '\x1A') p++;  // scan to ctrl-z or \n
            return p;                               // update input ptr
        }
    }
    return p0;
}

char* tokenize_pre_args(edlin_cmd_t* cmd, char* p) {
    char* p0 = p;                                   // copy of start of input
    while(!isalpha(*p)) p++;                        // scan over until candidate char
    for(int i = 0; i < 8; ++i) {           // search the char table
        if(toupper(*p) == EDLIN_TOKENS[i].ascii) {  // valid comand char
            int j = 0;                              // j arg counter
            cmd->token = EDLIN_TOKENS[i].token;     // tokenize
            if(p == p0) return p;                   // no pre args
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
    char* p0 = p;
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
        return p0;                                   // no valid chars
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
*/

/*
    //p = tokenize_post_args(cmd, p);                 // ?R,?S,T
    if(cmd->token) return p;                        // yes
   // p = tokenize_pre_args(cmd, p);                  // A,D,I,L,M,P,W
    if(cmd->token) return p;                        // yes
    p = tokenize_no_args(cmd, p);                   // ?,E,Q
    if(cmd->token) return p;                        // yes

    return tokenize_edit(cmd, p);                   // line edit or error
 */
/*
 * p0++;                       // no pre args
 else {
     *p = ',';                          // replace so CSV pre and post
     if(*(p - 1) == '?') cmd->query = true;
 }
 // tokenize CSV list of args
 if(*p0 == ',') {                        // check for current line syntax
     cmd->argv[j++] = p0++;              // store pointer to arg
 }
 char * arg = strtok(p0, ",?\x1A\n");       // tokenize by CSV, CTRL-Z
 while (arg != NULL && j < EDLIN_ARGC_MAX) {
     cmd->argv[j++] = arg;               // store pointer to arg
     arg = strtok(NULL, ",?\x1A\n");        // get next token
 }
 cmd->argc = j;                          // store argc
 while(*p != '\x1A' && *p != '\n') p++;  // scan to ctrl-z or \n
 return p;                               // update input ptr
 *
 */
