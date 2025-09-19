#include "edlin_config.h"
#include "edlin_errors.h"
#include <stdlib.h>
#include <stdio.h>

bool edlin_config(int argc, char* argv[], edlin_config_t* config) {
    config->filename = NULL;
    config->capacity = EDLIN_DEFAULT_CAPACITY;
    if(argc == 1) {
        return true;
    }
    for(int i = 1; i < argc; ++i) {
        printf("%s\n", argv[i]);
        if (argv[i][0] != '-') {
            if (config->filename != NULL) {
                edlin_panic(EDLIN_ERR_MULTIPLE_FILENAMES,"");
                return false;
            }
            config->filename = argv[i];
            continue;
        }
        switch (argv[i][1]) {
        case 'c':
            if (i + 1 >= argc) {
                edlin_panic(EDLIN_ERR_MISSING_ARG,"-c");
                return false;
            }
            config->capacity = (edlin_size_t)atoi(argv[++i]);
            break;
        default:
            edlin_panic(EDLIN_ERR_UKNOWN_OPT,argv[i]);
            return false;
        }
    }
    return true;
}

void edlin_print_config(edlin_config_t* config) {
    printf("%s %i\n",
        (config->filename) ?config->filename :"",
        config->capacity
    );
}
