#include "EDLIN/edlin_config.h"
#include "EDLIN/edlin_file.h"
#include "EDLIN/edlin_tokenize.h"
#include "EDLIN/edlin_errors.h"
#include "EDLIN/bios_keyboard_services.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    bios_key_t key = {0};
    bios_key_state_t state = {0};
    bios_keybd_info_t flags;

    while(key.parts.ascii != 'q') {
        bios_wait_for_keystroke_and_read(&key);
        printf("%i,%i\n", key.parts.ascii, key.parts.scan);
    }

    while(flags != BIOS_KEY_ALT) {
        bios_get_keyboard_flags(&flags);
        printf("%i\n", flags);
    }

    return EXIT_SUCCESS;
}

/*

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


while(cmd.token != TOK_QUIT) {
    edlin_read_line(&cmd.line, stdin);
    edlin_trim_line(&cmd.line);
    printf(">%s<\n", cmd.line);
    edlin_tokenize(&cmd);
    printf("token %i, %s\n", cmd.token, edlin_help(cmd.token));
    printf("argc %i\n", cmd.argc);
    for (int i = 0; i < EDLIN_ARGC_MAX; i++) {
        printf("tokens[%d] = \"%s\"\n", i, cmd.argv[i]);
    }
}
 */
