#include <stdio.h>
#include <stdlib.h>
#include "DOS/dos_memory.h"

int main(int argc, char* argv[]) {
    printf("EDLIN\n");

    printf("User memory = %lu", (dos_memory_available()));

    return EXIT_SUCCESS;
}
