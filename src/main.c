#include "EDLIN/edlin_types.h"
#include "EDLIN/edlin_edit.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    edlin_file_t* file;
    if(!edlin_init_file(argc, argv, file)) {
        return EXIT_FAILURE;
    }
    if(!edlin_edit(file)) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
