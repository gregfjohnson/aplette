/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "opt_codes.h"

/*
 * csize -- return size (in bytes) of a compiled string
 */
int csize(char* s) {
    int c, len;
    char* p;

    len = 1;
    p = s;
    while ((c = *p++) != END) {
        int i = 0;
        len++;
        c &= 0377;

        switch (c) {
        default:
            break;

        case QUOT:
            i = *p++;
            break;

        case CONST:
            i = *p++;
            i *= SDAT;
            len++;
            break;

        case NAME: case FUN: case ARG1: case ARG2: case AUTO: case REST: case RVAL:
            i = SPTR;
            break;
        }
        p += i;
        len += i;
    }

    return (len);
}
