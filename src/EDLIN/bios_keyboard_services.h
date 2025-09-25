/**
* @url https://www.stanislavs.org/helppc/int_16.html
*
*   INT 16,0   Wait for keystroke and read
* 	INT 16,1   Get keystroke status
* 	INT 16,2   Get shift status
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

typedef union {
    uint16_t key;
    typedef struct {  
        uint8_t ascii;
        uint8_t scan;
    } parts;
} bios_key_t

typedef uint8_t bios_keybd_info_t;

#define BIOS_KEYBOARD_SERVICES    16h

#define BIOS_WAIT_FOR_KEYSTROKE_AND_READ      0
#define BIOS_GET_KEYSTROKE_STATUS             1 
#define BIOS_GET_SHIFT_STATUS                 2
#define BIOS_SET_KEYBOARD_TYPEMATIC           3
#define BIOS_KEYBOARD_CLICK_ADJUSTMENT        4
#define BIOS_KEYBOARD_BUFFER_WRITE            5

// #define BIOS_WAIT_FOR_KEYSTROKE_AND_READ      10
// #define BIOS_GET_KEYSTROKE_STATUS             11
// #define BIOS_GET_SHIFT_STATUS                 12

bios_key_t wait_for_keystroke_and_read();

bios_key_t get_keystroke_status();

bios_keybd_info_t get_shift_status();

void set_keyboard_typematic(uint8_t mode, uint8_t delay, uint8_t rate);

void keyboard_click_adjustment(bool state);

bool keyboard_buffer_write(bios_key_t key);

// wait_for_keystroke_and_read
// get_keystroke_status
// get_shift_status

#endif
