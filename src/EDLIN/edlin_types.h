#ifndef EDLIN_TYPES_H
#define EDLIN_TYPES_H

#include "edlin_constants.h"
#include <stdint.h>

typedef uint16_t edlin_size_t;

typedef char edlin_line_t[EDLIN_LINE_SIZE];

typedef struct {
    const char *filename;
    edlin_size_t capacity;
    bool help;
    bool verbose;
} edlin_config_t;

typedef struct {
    edlin_line_t path;
    edlin_line_t* lines;
    edlin_size_t size;
    edlin_size_t capacity;
} edlin_file_t;

#endif
