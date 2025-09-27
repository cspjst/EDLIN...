#include "EDLIN/edlin_config.h"
#include "EDLIN/edlin_file.h"
#include "EDLIN/edlin_tokenize.h"
#include "EDLIN/edlin_parse.h"
#include "EDLIN/edlin_errors.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    edlin_config_t config;
    edlin_cmd_t cmd;
    if(!edlin_config(argc, argv, &config)) {
        edlin_usage();
        return EXIT_FAILURE;
    }
    edlin_intro();
    edlin_file_t* file = edlin_new_file(
        config.filename,
        config.capacity
    );
    if(!file) {
        edlin_panic(EDLIN_ERR_ALLOC,"");
        return EXIT_FAILURE;
    }
    edlin_load_file(file);
    printf("%s: %i lines read\n", file->path, file->size);

    do {
        printf("*");
        edlin_read_line(&cmd.line, stdin);
        edlin_trim_line(&cmd.line);
        edlin_tokenize(&cmd);
    } while(edlin_parse(&cmd, file));
    return EXIT_SUCCESS;
}
