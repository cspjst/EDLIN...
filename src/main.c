#include "EDLIN/edlin_file.h"
#include "EDLIN/edlin_config.h"
#include "EDLIN/edlin_tokenize.h"
#include "EDLIN/edlin_types.h"
//#include "EDLIN/edlin_debug.h"
//#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    edlin_line_t input;
    edlin_cmd_t cmd;
    edlin_file_t* file = edlin_new_file();
    edlin_intro();
    if (file && edlin_config(argc, argv, file)) {
        edlin_read_line(&input, stdin);
        const char* p = input;
        //while(cmd.token != TOK_ERROR) {
            p = edlin_tokenize(&cmd, p);
            printf("token=%i argc=%i >%s<\n", cmd.token, cmd.argc, cmd.argv[0]);
            p++;

            //}
    }

    edlin_free_file(file);

    return EXIT_SUCCESS;
}
