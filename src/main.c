#include "EDLIN/edlin_types.h"
#include "EDLIN/edlin_edit.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if(edlin_config_parse(argc, argv)) {
        edlin_file_t* file = edlin_new_file();
        if(!file) {
            edlin_panic(EDLIN_ERR_ALLOC);
            return EXIT_FAILURE;
        }
        edlin_print_file(file);
        while(edlin_edit(file));
    }
    return EXIT_SUCCESS;
}
