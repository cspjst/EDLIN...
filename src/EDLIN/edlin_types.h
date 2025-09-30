#ifndef EDLIN_TYPES_H
#define EDLIN_TYPES_H

#include "edlin_constants.h"
#include <stdint.h>
#include <stdbool.h>

typedef uint16_t edlin_size_t;

// use sequential char values to in-place tokenize and make separating out command types easier using > and <
typedef enum {
    TOK_ERROR = 0,  // error

    TOK_EDIT = 'A', // A    line# Edit a single line
    // no arg commands
    TOK_HELP,       // B    ? Show help
    TOK_END,        // C    E End (save file)
    TOK_QUIT,       // D    Q Quit (throw away changes)
    // pre command arg(s)
    TOK_APPEND,     // E    [#lines]A Append a line below the mark
    TOK_COPY,       // F    [range],toline[,times]C	Copy lines
    TOK_DELETE,     // G    [range]D Delete lines
    TOK_INSERT,     // H    [line]I Insert new lines before the mark
    TOK_LIST,       // I    [range]L	List the file (mark at top unless set elsewhere)
    TOK_MOVE,       // J    [range],tolineM Move lines
    TOK_PAGE,       // K    [range]P	Page (same as List, but mark end of list)
    TOK_WRITE,      // L    [#lines]W Write the file to disk
    // pre & post query commnnd arg(s)
    TOK_REPLACE,    // M    [range][?]Rold,new Replace text
    TOK_SEARCH,     // N    [range][?]S[string] Search for text
    // pre & post commnnd args
    TOK_TRANSFER,   // O    [toline]Tfilepath Transfer (insert the contents of a new file at the mark)
    // special cases
    TOK_EMPTY,      // P    user hit return on whitespace line
    TOK_QUERY,      // Q    ? is interactive
    // error states
    TOK_SYNTAX,     // R    command ok but args wrong
    TOK_UNKNOWN     // S
} enum_token_t;

typedef char edlin_line_t[EDLIN_LINE_SIZE];

typedef struct {
    char* filepath;
    bool ignoreCRTLZ;
    edlin_line_t** lines;   // array of pointers to line buffers
    edlin_size_t pos;       // insert position line number
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_file_t;

typedef struct {
    enum_token_t token;
    edlin_size_t argc;
    const char* argv[EDLIN_ARGC_MAX];
    bool query;
} edlin_cmd_t;

typedef struct {
    char ascii;
    enum_token_t token;
} edlin_token_t;

#endif
