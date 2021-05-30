/**
 * CS537 SP2021 - DIS W2
 * Example application source code.
 *
 * Copyright 2021 Guanzhou Hu
 */


/**
 * Includes header of a local library.
 * The library's implementation could either be dynamically linked or
 * staticly linked with this application executable.
 */
#include "example-lib.h"


int
main(void) {
    lib_print_hello("my friend");

    return 0;
}