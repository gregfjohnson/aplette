/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"

data
    ex_not(d)
        data d;
{
    if (d == zero)
        return (one);
    return (zero);
}
