#ifndef EDLIN_EDIT_H
#define EDLIN_EDIT_H

#include "edlin_types.h"
#include <stdio.h>

edlin_file_t* edlin_new_file(const edlin_line_t path, edlin_size_t capacity);

void edlin_free_file(edlin_file_t* file);

edlin_line_t* edlin_new_line();

bool edlin_read_line(edlin_line_t* line, FILE* istream);

void edlin_trim_line(edlin_line_t* line);

bool edlin_load_file(edlin_file_t* file);

void edlin_print_file(edlin_file_t* file);

char edlin_edit(edlin_file_t* file);

#endif
