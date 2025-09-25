/**
* INT 16h Detailed Function List
* Function	                            (AH)	    Device	    Inputs	                        System   Return
* Read key press	                      0h	      Keyboard	  None	                        PC/XT    AH[1] = Scan code of the key pressed down	AL = ASCII character of the button pressed
* Get the State of the keyboard buffer	  1h	      Keyboard	  None	                        PC/XT    AH = Scan code, ZF = 0 if key pressed down	AL = ASCII character, AX = 0 if no Scan codes
* Get the State of the keyboard	          2h	      Keyboard	  None	                        PC/XT    AH = BIOS Keyboard flags
* Establish repetition factor	          3h	      Keyboard	  AL = Mode                     AT+      None 
*                                                                 BH = Repeat delay (if AL = 5) 
*                                                                 BL = Typematic rate	
* Keyboard Click adjustment	              4h	      Keyboard	  AL = 0 (off) or 1 (on)	    AT+      None
* Simulate a keystroke	                  5h	      Keyboard	  CH = Scan code                AT,PS/2  AL = 0 If successful, 1 otherwise
*                                                                 CL = ASCII Character	        
*/
#include "bios_keyboard_services.h" 

bios_key_t wait_for_keystroke_and_read() {
  
}

bios_key_t get_keystroke_status() {
  
}

bios_keybd_info_t get_shift_status() {
  
}

void set_keyboard_typematic(uint8_t mode, uint8_t delay, uint8_t rate) {
  
}

void keyboard_click_adjustment(bool state) {
  
}

bool keyboard_buffer_write(bios_key_t key) {
  
}
