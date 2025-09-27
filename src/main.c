#include "EDLIN/edlin_file.h"
#include "EDLIN/edlin_config.h"
#include "EDLIN/edlin_debug.h"
//#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {

    edlin_file_t* file = edlin_new_file();

    if (file && edlin_config(argc, argv, file)) {
        debug_file_t(file);
    }

    edlin_free_file(file);

    return EXIT_SUCCESS;
}
