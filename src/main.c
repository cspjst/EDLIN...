#include "EDLIN/edlin_config.h"
#include "EDLIN/edlin_file.h"
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
    edlin_read_line(&cmd.line, stdin);
    edlin_trim_line(&cmd.line);
    printf(">%s<", cmd.line);
    printf("token %i", edlin_cmd_token('c'));
    return EXIT_SUCCESS;
}
