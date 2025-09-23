#ifndef EDLIN_PARSE_H
#define EDLIN_PARSE_H

#include "edlin_constants.h"
#include "edlin_types.h"

#define EDLIN_ARGC_MAX 5

typedef enum {
    TOK_EDIT = 0,   // line# Edit a single line
    TOK_HELP,       // ? Show help
    TOK_END,        // E End (save file)
    TOK_QUIT,       // Q Quit (throw away changes)
    TOK_APPEND,     // [#lines]A Append a line below the mark
    TOK_COPY,       // [range],toline[,times]C	Copy lines
    TOK_DELETE,     // [range]D Delete lines
    TOK_INSERT,     // [line]I Insert new lines before the mark
    TOK_LIST,       // [range]L	List the file (mark at top unless set elsewhere)
    TOK_MOVE,       // [range],tolineM Move lines
    TOK_PAGE,       // [range]P	Page (same as List, but mark end of list)
    TOK_WRITE,      // [#lines]W Write the file to disk
    TOK_REPLACE,    // [range][?]Rold,new Replace text
    TOK_SEARCH,     // [range][?]S[string] Search for text
    TOK_TRANSFER,   // [toline]Tfilepath Transfer (insert the contents of a new file at the mark)
    TOK_ERROR,      // recognised command but syntax error
    TOK_EMPTY,      // user hit return on whitespace line
    TOK_UNKNOWN
} edlin_token_t;

typedef struct {
    edlin_line_t line;
    edlin_token_t op;
    edlin_size_t argc;
    char* argv[EDLIN_ARGC_MAX];
} edlin_cmd_t;

char* edlin_help(edlin_size_t i);

void edlin_tokenize(edlin_cmd_t* cmd);

#endif
