/**
* @url https://www.stanislavs.org/helppc/int_16.html
*
*   INT 16,0   Wait for keystroke and read
* 	INT 16,1   Get keystroke status
* 	INT 16,2   Read Keyboard Flags
* 	INT 16,3   Set keyboard typematic rate (AT+)
* 	INT 16,4   Keyboard click adjustment (AT+)
* 	INT 16,5   Keyboard buffer write  (AT,PS/2 enhanced keyboards)
* 	INT 16,10  Wait for keystroke and read  (AT,PS/2 enhanced keyboards)
* 	INT 16,11  Get keystroke status  (AT,PS/2 enhanced keyboards)
* 	INT 16,12  Get shift status  (AT,PS/2 enhanced keyboards)
*/
#ifndef BIOS_KEYBOARD_SERVICES_H
#define BIOS_KEYBOARD_SERVICES_H

#include <stdint.h>

#define BIOS_KEY_RIGHT_SHIFT    1
#define BIOS_KEY_LEFT_SHIFT     2
#define BIOS_KEY_CTRL           4
#define BIOS_KEY_ALT            8
#define BIOS_SCROLL_LOCK        16
#define BIOS_NUM_LOCK           32
#define BIOS_CAPS_LOCK          64
#define BIOS_KEY_INSERT         128

typedef uint8_t bios_keybd_info_t;

#pragma pack(1)
typedef struct {
    uint8_t ascii;
    uint8_t scan;
} bios_key_parts_t;
#pragma pack()

typedef union {
    uint16_t combined;
    bios_key_parts_t parts;
} bios_key_t;

#pragma pack(1)
typedef struct {
    bios_key_t key;
    uint8_t is_pressed;
} bios_key_state_t;
#pragma pack()

#define BIOS_KEYBOARD_SERVICES    16h

#define BIOS_WAIT_FOR_KEYSTROKE_AND_READ      0
#define BIOS_GET_KEYSTROKE_STATUS             1
#define BIOS_GET_SHIFT_STATUS                 2

void bios_wait_for_keystroke_and_read(bios_key_t* key);

void bios_get_keystroke_status(bios_key_state_t* key_state);

void bios_get_keyboard_flags(bios_keybd_info_t* flags);

// void bios_set_keyboard_typematic(uint8_t mode, uint8_t delay, uint8_t rate);
// void bios_keyboard_click_adjustment(bool state);
// bool bios_keyboard_buffer_write(bios_key_t key);
// bios_wait_for_keystroke_and_read
// bios_get_keystroke_status
// bios_get_shift_status

#endif
