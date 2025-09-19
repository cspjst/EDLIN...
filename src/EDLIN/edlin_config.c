#include "edlin_config.h" 

bool edlin_config((int argc, char* argv[], edlin_config_t* config) {
    if(argc == 1) {
        config->filename = NULL;
        config->capacity = EDLIN_DEFAULT_CAPACITY;
        config->help = false;
        config->verbose = false;
    }
    for(int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            if (config->filename != NULL) {
                edlin_panic(EDLIN_ERR_MULTIPLE_FILENAMES);
                return false;
            }
            config->filename = argv[i];
            continue;
        }
         switch (argv[i][1]) {
            case 'c':
                if (i + 1 >= argc) {
                    edlin_panic(EDLIN_ERR_MISSING_ARG);
                    return false;
                }
                config->capacity = (edlin_size_t)atoi(argv[++i]);
                break;                
            case 'h':
            case 'v':
            default:
                edlin_panic(EDLIN_ERR_UKNOWN_OPT);
                return false;
         }
    }
}
