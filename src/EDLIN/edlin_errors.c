#include "edlin_errors.h"
#include <stdio.h>

const char* const EDLIN_ERROR_MESSAGES[] = {
    "NULL Pointer!",
    "Missing argument!",
    "Multiple filenames!",
    "Unknown option!",
    "Memory allocation fail!",
    "Text buffer full!",
    "Stream read/write fail!"
};

void* edlin_panic(edlin_err_t e, const char* context) {
  printf("%s %s\n",
      EDLIN_ERROR_MESSAGES[e],
      context
  );
  return NULL;
}
