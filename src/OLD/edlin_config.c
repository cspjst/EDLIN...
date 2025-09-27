#include "edlin_config.h"
#include "edlin_errors.h"
#include <stdlib.h>
#include <stdio.h>

static const char EDLIN_INTRO[] = " \
\nEDLIN 0.01, copyright (c) 2025 Jeremy Thornton\n\
This program comes with ABSOLUTELY NO WARRANTY.\n\
It is free software, and you are welcome to redistribute it\n\
under the terms of the MIT License.\n\n\
";

static const char EDLIN_USAGE[] = " usage: EDLIN file_name [-c <max lines>]";

static const char EDLIN_MSG_FILENAME[] = "File name must be specified";

void edlin_intro() {
    printf("%s", EDLIN_INTRO);
}

void edlin_usage() {
    printf("%s", EDLIN_USAGE);
}

bool edlin_config(int argc, char* argv[], edlin_config_t* config) {
    config->filename = NULL;
    config->capacity = EDLIN_DEFAULT_CAPACITY;
    if(argc == 1) {
        edlin_panic(EDLIN_ERR_MISSING_ARG, EDLIN_MSG_FILENAME);
        return false;
    }
    for(int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            if (config->filename != NULL) {
                edlin_panic(EDLIN_ERR_MULTIPLE_FILENAMES,argv[i]);
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
    if(!config->filename) {
        edlin_panic(EDLIN_ERR_MISSING_ARG, EDLIN_MSG_FILENAME);
        return false;
    }
    return true;
}
