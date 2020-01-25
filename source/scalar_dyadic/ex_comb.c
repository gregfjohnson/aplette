/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include <math.h>

data ex_comb(data c1, data c2) {
    double f;
    double d1, d2;

    if (fabs(cimag(c1)) > creal(tolerance)
        || fabs(cimag(c2)) > creal(tolerance))
    {
        error(ERR_domain, "cannot comb complex values");
    }

    d1 = creal(c1);
    d2 = creal(c2);

    if (d1 > d2)
        return (zero);

    f = gamma(d2 + 1.) - gamma(d1 + 1.) - gamma(d2 - d1 + 1.);

    if (f > MAXEXP)
        error(ERR_limit, "input range overflow");

    d1 = exp(f);

    return (d1);
}
