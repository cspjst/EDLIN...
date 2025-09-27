#include <stdio.h>
#include <stdlib.h>
#include "DOS/dos_memory.h"

int main(int argc, char* argv[]) {

    printf("User memory = %lu bytes free", dos_memory_available() - DOS_MCB_OVERHEAD);

    return EXIT_SUCCESS;
}
