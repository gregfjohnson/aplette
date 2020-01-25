/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "math.h"

data
    ex_sgn(d)
        data d;
{
    double r;

    if (fabs(cimag(d)) > creal(tolerance)) {
        error(ERR_domain, "signum value not a real value");
    }

    r = creal(d);
    if (r == creal(zero))
        return (zero);

    if (r < creal(zero))
        return (-one);

    return (one);
}
