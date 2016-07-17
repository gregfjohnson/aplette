/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"
#include "memory.h"
#include "userfunc.h"

char *
    catcode(s1, s2) char *s1,
    *s2;
{
    int i, j;
    char *p, *q;

    i = csize(s1) - 1;
    j = csize(s2);
    p = q = alloc(i + j);
    p += copy(CH, s1, p, i);
    copy(CH, s2, p, j);
    return (q);
}
