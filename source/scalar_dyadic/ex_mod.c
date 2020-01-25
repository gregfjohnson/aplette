/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include <math.h>
#include "utility.h"

data
    ex_mod(d1, d2)
        data d1,
    d2;
{
    double dd1, dd2;

    /* x mod 0 is defined to be x */
    if (d1 == zero)
        return (d2);

    if (fabs(cimag(d1)) > creal(tolerance)
        || fabs(cimag(d2)) > creal(tolerance))
    {
        error(ERR_domain,
              "modular arithmetic is not defined on complex numbers");
    }

    dd1 = creal(d1);
    dd2 = creal(d2);

    dd2 = dd2 - dd1 * floor(MINFLOAT + dd2 / dd1);

    if (fabs(dd2) < creal(tolerance))
        return (0);

    if (fabs(dd2 - dd1) < creal(tolerance))
        return (0);

    if (dd2 == dd1)
        return (0);

    return (dd2);
}
