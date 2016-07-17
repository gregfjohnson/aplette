/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "local_parser.h"

static void flop(char* a, char* b)
{
    char *a1, *a2;
    int c;

    a1 = a;
    a2 = b;
    while (a1 < a2) {
        c = *a1;
        *a1++ = *--a2;
        *a2 = c;
    }
}

void invert(char* a, char* b)
{
    flop(a, b);
    flop(b, ccharp);
    flop(a, ccharp);
}
