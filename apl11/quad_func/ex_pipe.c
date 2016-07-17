/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "utility.h"

void ex_pipe()
{
    struct item* p;
    int pp[2];

    SECURITY_CHECK;
    if (pipe(pp) == -1)
        p = newdat(DA, 1, 0);
    else {
        p = newdat(DA, 1, 2);
        p->datap[0] = pp[0];
        p->datap[1] = pp[1];
    }
    pop();
    *sp++ = p;
}
