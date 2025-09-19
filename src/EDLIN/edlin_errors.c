#include "edlin_errors.h"
#include <stdio.h>

const char* const EDLIN_ERROR_MESSAGES[] = {
    "Success!",
    "Missing argument!",
    "Multiple filenames!",
    "Unknown option!"
};

void* edlin_panic(edlin_err_t e, const char* context) {
  printf("%s %s\n",
      EDLIN_ERROR_MESSAGES[e],
      context
  );
  return NULL;
}
