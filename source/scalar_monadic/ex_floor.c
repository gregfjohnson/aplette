/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include <math.h>

data
    ex_floor(d)
        data d;
{
    d = floor(d + tolerance);
    return (d);
}
