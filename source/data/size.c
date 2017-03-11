/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

int size()
{
    int i, s;

    s = 1;
    for (i = idx.rank - 1; i >= 0; i--) {
        idx.del[i] = s;
        s *= idx.dim[i];
    }
    idx.size = s;
    return (s);
}
