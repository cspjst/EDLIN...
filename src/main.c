#include "EDLIN/edlin_config.h"
#include "EDLIN/edlin_types.h"
#include "EDLIN/edlin_edit.h"
#include "EDLIN/edlin_errors.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    edlin_config_t config;
    if(!edlin_config(argc, argv, &config)) {
        edlin_usage();
        return EXIT_FAILURE;
    }
    edlin_intro();
    edlin_file_t* file = edlin_new_file(
        (const edlin_line_t*)config.filename,
        config.capacity
    );
    if(!file) {
        edlin_panic(EDLIN_ERR_ALLOC,"");
        return EXIT_FAILURE;
    }
    edlin_read_file(file);
    edlin_print_file(file);
    return EXIT_SUCCESS;
}

/*
if(edlin_config_parse(argc, argv, &config)) {
    edlin_file_t* file = edlin_new_file();
    if(!file) {
        edlin_panic(EDLIN_ERR_ALLOC);
        return EXIT_FAILURE;
    }
    edlin_print_file(file);
    while(edlin_edit(file) != 'q');
    edlin_free_file(file);
}
*/
