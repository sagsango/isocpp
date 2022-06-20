/*
# getenv

# Envoronment variables

    Returns NULL if not found.
*/

#include "common.h"

int main(void) {
    printf("HOME = %s\n", getenv("HOME"));
    assert(getenv("NOT_DEFINED") == NULL);
    return EXIT_SUCCESS;
}
