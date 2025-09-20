#ifndef EDLIN_PARSE_H
#define EDLIN_PARSE_H

typedef enum {
    TOK_HELP = 0,   // ? Show help
    TOK_EDIT,       // line# Edit a single line
    TOK_APPEND,     // [#lines]A Append a line below the mark
    TOK_COPY,       // [range],toline[,times]C	Copy lines
    TOK_DELETE,     // [range]D Delete lines
    TOK_END,        // E End (save file)
    TOK_INSERT,     // [line]I Insert new lines before the mark
    TOK_LIST,       // [range]L	List the file (mark at top unless set elsewhere)
    TOK_MOVE,       // [range],tolineM Move lines
    TOK_PAGE,       // [range]P	Page (same as List, but mark end of list)
    TOK_QUIT,       // Q Quit (throw away changes)
    TOK_REPLACE,    // [range][?]Rold,new Replace text
    TOK_SEARCH,     // [range][?]S[string] Search for text
    TOK_TRANSFER,   // [toline]Tfilename Transfer (insert the contents of a new file at the mark)
    TOK_WRITE,      // [#lines]W Write the file to disk


} edlin_token_t;

#endif
