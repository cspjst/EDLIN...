/**
* INT 16h Detailed Function List
* Function	                            (AH)	    Device	    Inputs	                      Return
* Read key press	                        0h	      Keyboard	  None	                        AH[1] = Scan code of the key pressed down	AL = ASCII character of the button pressed
* Get the State of the keyboard buffer	  1h	      Keyboard	  None	                        AH = Scan code, ZF = 0 if key pressed down	AL = ASCII character, AX = 0 if no Scan codes
* Get the State of the keyboard	          2h	      Keyboard	  None	                        AH = BIOS Keyboard flags
* Establish repetition factor	            3h	      Keyboard	  AL = Mode                     None 
*                                                               BH = Repeat delay (if AL = 5) 
*                                                               BL = Typematic rate	
* Keyboard Click adjustment	              4h	      Keyboard	  AL = 0 (off) or 1 (on)	      None
* Simulate a keystroke	                  5h	      Keyboard	  CH = Scan code
*                                                               CL = ASCII Character	        AL = 0 If successful, 1 otherwise
* Get the ID of the keyboard	            Ah	      Keyboard	  None	                        AL = Keyboard Id
*/
#ifndef BIOS_KEYBOARD_SERVICES_H
#define BIOS_KEYBOARD_SERVICES_H

#define BIOS_KEYBOARD_SERVICES    16h



#endif
