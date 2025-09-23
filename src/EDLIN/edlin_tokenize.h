#ifndef EDLIN_PARSE_H
#define EDLIN_PARSE_H

#include "edlin_constants.h"
#include "edlin_types.h"

char* edlin_help(edlin_size_t i);

void edlin_tokenize(edlin_cmd_t* cmd);

#endif
