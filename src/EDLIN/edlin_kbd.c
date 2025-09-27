#include "edlin_kbd.h"
#include "../BIOS/bios_keyboard_services.h"
#include "../BIOS/bios_keyboard_scan_codes.h"
#include <stdio.h>

char edlin_kbd_key_char() {
    bios_key_t key;
    bios_wait_for_keystroke_and_read(&key);
    return key.parts.ascii;
}

char edlin_kbd_scan_code()  {
    bios_key_t key;
    bios_wait_for_keystroke_and_read(&key);
    return key.parts.scan;
}

bool edlin_kbd_yesno(const char* question) {
    printf("%s(Y/N)?", question);
    fflush(stdout);
    bool result = (edlin_kbd_scan_code() == SCAN_Y);
    if (!result) printf("\n");
    return result;
}
