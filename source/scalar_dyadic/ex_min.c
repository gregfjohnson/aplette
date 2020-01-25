/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include <math.h>
#include "utility.h"

data
    ex_min(d1, d2)
        data d1,
    d2;
{
    if (fabs(cimag(d1)) > creal(tolerance)
        || fabs(cimag(d2)) > creal(tolerance))
    {
        error(ERR_domain, "cannot sort complex values");
    }
    if (creal(d1) < creal(d2))
        return (d1);
    return (d2);
}
