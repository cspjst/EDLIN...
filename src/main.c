#include "EDLIN/edlin_types.h"
#include "EDLIN/edlin_edit.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    edlin_file_t* file = edlin_init_file(argc, argv);
    if(!file) {
        return EXIT_FAILURE;
    }
    edlin_print_file(file);
    if(!edlin_edit(file)) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
