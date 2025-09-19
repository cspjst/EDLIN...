#include "edlin_edit.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    file->capacity = capacity;
    file->size = 0;
    if(!path) {
        file->path[0] = '\0';
        return file;
    }
    strcpy((char*)&file->path, (const char*)path);
    //edlin_read_file(file->path);
    return file;
}

void edlin_free_file(edlin_file_t* file) {
    if(file) {
        free(file->lines);
        free(file);
    }
}

edlin_file_t* edlin_init_file(int argc, char* argv[]) {
    edlin_file_t* file = edlin_new_file("", 99);
    return file;
}

void edlin_print_file(edlin_file_t* file) {
    for(edlin_size_t i = 0; i < file->size; ++i) {
        printf("%s\n", file->lines[i]);
    }
    printf("path \"%s\" size %u capacity %u\n",
        (*file->path) ?file->path :"",
        file->size,
        file->capacity
    );
}

char edlin_edit(edlin_file_t* file) {
  // do commands and return command type
  return 'q';
}
