/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"

data
    ex_or(d1, d2)
        data d1,
    d2;
{
    if (d1 != zero || d2 != zero)
        return (one);
    return (zero);
}
