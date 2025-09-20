#include "edlin_file.h"
#include "edlin_errors.h"
#include "edlin_types.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


edlin_file_t* edlin_new_file(const edlin_line_t path, edlin_size_t capacity) {
    edlin_file_t* file = malloc(sizeof(edlin_file_t));
    if (!file) {
        return NULL;
    }
    file->lines = calloc(capacity, sizeof(edlin_line_t*));  // arrray of null line pointers
    if (!file->lines) {
        free(file);
        return NULL;
    }
    strcpy(file->path, path);
    file->capacity = capacity;
    file->size = 0;
    return file;
}

void edlin_free_file(edlin_file_t* file) {
    if(!file) {
        return;
    }
    if (file->lines) {
        for (edlin_size_t i = 0; i < file->size; i++) {
            free(file->lines[i]);
        }
        free(file->lines);
    }
    free(file);
}

bool edlin_yesno() {
    printf("Continue (Y/N)?");
    fflush(stdout);
    return toupper(getchar()) == 'Y';
}

edlin_line_t* edlin_new_line() {
     edlin_line_t* line = calloc(1, EDLIN_LINE_SIZE);
     if(!line) {
         edlin_panic(EDLIN_ERR_ALLOC, "new line failed!");
     }
     return line;
}

// Read a line from input stream into buffer
bool edlin_read_line(edlin_line_t* line, FILE* istream) {
    if (!fgets((char*)line, EDLIN_LINE_SIZE, istream)) {
        if (feof(istream)) {
            return false;  // Graceful EOF indication
        } else {
            edlin_panic(EDLIN_ERR_STREAM, "read line failed!");
            return false;
        }
    }
    return true;
}

void edlin_trim_line(edlin_line_t* line) {
    if (!line) {
        edlin_panic(EDLIN_ERR_NULL, "trim line failed!");
        return;
    }
    (*line)[strcspn((const char*)line, "\n")] = '\0';
}

bool edlin_is_file_full(edlin_file_t* file, edlin_size_t count) {
    bool is_full = (file->size + count > file->capacity);
    if(is_full) {
        edlin_panic(EDLIN_ERR_BUFFER_FULL, "\n");
    }
    return is_full;
}

bool edlin_load_file(edlin_file_t* file) {
    if (!file) {
        edlin_panic(EDLIN_ERR_NULL, "Null pointer in load file");
        return false;
    }
    FILE* f = fopen((const char*)file->path, "r");
    if (!f) {
        file->size = 0;
        return true;    // create file when save
    }
    file->size = 0;
    edlin_line_t* line;
    bool reading = true;

    while (reading) {
        if (edlin_is_file_full(file, 1)) {
            fclose(f);
            return false;
        }
        line = edlin_new_line();
        if (!line) {
            fclose(f);
            return false;
        }
        if (!edlin_read_line(line, f)) {
            free(line);
            reading = false;

            continue;
        }
        edlin_trim_line(line);
        file->lines[file->size++] = line;
    }

    fclose(f);
    return true;
}

void edlin_print_file(edlin_file_t* file) {
    for(edlin_size_t i = 0; i < file->size; ++i) {
        printf("%s\n", *file->lines[i]);
        if (
            (i + 1) % EDLIN_PAGE_SIZE == 0
            && i + 1 < file->size
            && !edlin_yesno()
        ) {
            printf("\n");
            return;
        }
    }
}
