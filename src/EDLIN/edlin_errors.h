#ifndef EDLIN_ERRORS_H
#define EDLIN_ERRORS_H

typedef enum {
    EDLIN_ERR_NULL = 0,
    EDLIN_ERR_MISSING_ARG,
    EDLIN_ERR_MULTIPLE_FILENAMES,
    EDLIN_ERR_UKNOWN_OPT,
    EDLIN_ERR_ALLOC,
    EDLIN_ERR_BUFFER_FULL,
    EDLIN_ERR_STREAM,

    EDLIN_ERR_ENTRY
} edlin_err_t;

void* edlin_panic(edlin_err_t e, const char* context);

#endif
