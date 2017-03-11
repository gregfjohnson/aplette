/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include <math.h>

data
    ex_mod(d1, d2)
        data d1,
    d2;
{
    /* x mod 0 is defined to be x */
    if (d1 == zero)
        return (d2);
    d2 = d2 - d1 * floor(MINFLOAT + d2 / d1);
    if (fabs(d2) < tolerance)
        return (0);
    if (fabs(d2 - d1) < tolerance)
        return (0);
    if (d2 == d1)
        return (0);
    return (d2);
}
