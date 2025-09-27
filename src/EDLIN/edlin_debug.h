#ifndef EDLIN_DEBUG_H
#define EDLIN_DEBUG_H

#include "edlin_types.h"
#include <stdio.h>

void debug_file_t(edlin_file_t* file) {
    printf("file %s\nctrl-z %u\npos %u\nsize %u\ncapacity %u\n",
        file->filepath,
        file->ignoreCRTLZ,
        file->pos,
        file->size,
        file->capacity
    );
}

#endif
