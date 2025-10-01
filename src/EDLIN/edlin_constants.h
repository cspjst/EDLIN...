#ifndef EDLIN_CONSTANTS_H
#define EDLIN_CONSTANTS_H

// ASCII control codes
//#define CTRL_C        // ETX  end of text
//#define CTRL_Z        // edlin uses to encode control chars
#define CTRL_Z  '\x1A'      // SUB  substitute

#define EDLIN_LINE_SIZE  256
#define EDLIN_PAGE_SIZE 23
#define EDLIN_ARGC_MAX 5

#endif
