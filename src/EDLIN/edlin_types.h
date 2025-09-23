#ifndef EDLIN_TYPES_H
#define EDLIN_TYPES_H

#include "edlin_constants.h"
#include <stdint.h>
#include <stdbool.h>

typedef uint16_t edlin_size_t;

typedef char edlin_line_t[EDLIN_LINE_SIZE];

typedef struct {
    edlin_line_t path;
    edlin_line_t** lines;   // array of pointers to line buffers
    edlin_size_t pos;       // insert position line number
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_file_t;

typedef struct {
    edlin_line_t line;
    edlin_token_t op;
    edlin_size_t argc;
    char* argv[EDLIN_ARGC_MAX];
} edlin_cmd_t;

#endif
