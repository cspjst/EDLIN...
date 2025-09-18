#include "edlin_edit.h"
#include <string.h>
#include <stdlib.h>

edlin_file_t* edlin_new_file(const edlin_line_t* path, edlin_size_t capacity) {
    edlin_file_t* file = malloc(sizeof(edlin_file_t));
    if (!file) {
        return NULL;
    }
    file->lines = calloc(capacity, sizeof(edlin_line_t));
    if (!file->lines) {
        free(file);
        return NULL;
    }
    strcpy((char*)&file->path, (const char*)path);
    file->capacity = capacity;
    file->size = 0;
    return file;
}

void edlin_free_file(edlin_file_t* file) {
    if(file) {
        free(file->lines);
        free(file);
    }
}

bool edlin_init_file(int argc, char* argv[], edlin_file_t* file) {
    return true;
}

// main edit loop
bool edlin_edit(edlin_file_t* file) {
  // loop until 'q' or 'e'
  return true;
}
