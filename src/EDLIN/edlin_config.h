#ifndef EDLIN_CONFIG_H
#define EDLIN_CONFIG_H

#include "edlin_types.h"

typedef struct {
    const char* filename;
    edlin_size_t capacity;
} edlin_config_t;

void edlin_intro();

void edlin_usage();

bool edlin_config(int argc, char* argv[], edlin_config_t* config);

#endif
