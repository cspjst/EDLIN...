#ifndef EDLIN_KBD_H
#define EDLIN_KBD_H

#include <stdbool.h>

char edlin_kbd_key_char();

char edlin_kbd_scan_code();

bool edlin_kbd_yesno(const char* question);

#endif
