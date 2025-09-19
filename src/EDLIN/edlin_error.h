#ifndef EDLIN_ERROR_H
#define EDLIN_ERROR_H

typedef enum {
    EDLIN_SUCCESS = 0,

    EDLIN_ERR_MISSING_ARG,
    EDLIN_ERR_MULTIPLE_FILENAMES,
    EDLIN_ERR_UKNOWN_OPT
} edlin_err_t;

void* edlin_panic(edlin_err_t e); 

#endif
