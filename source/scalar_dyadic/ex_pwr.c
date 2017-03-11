/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include <math.h>

data
    ex_pwr(d1, d2)
        data d1,
    d2;
{
    int s;
    double f1, f2;

    s = 0;
    f1 = d1;
    if (f1 > 0.) {
        f1 = d2 * log(f1);
        goto chk;
    }
    if (f1 == 0.)
        return (d2 == zero ? (data)1.0 : zero);

    /* check for integer exponent */
    f2 = floor(d2);
    if (fabs(d2 - f2) < tolerance) {
        s = (int)f2 % 2;
        f1 = d2 * log(fabs(f1));
        goto chk;
    }
    /* should check rational d2 here */
    goto bad;

chk:
    if (f1 < MAXEXP) {
        d1 = exp(f1);
        if (s)
            d1 = -d1;
        return (d1);
    }
bad:
    error(ERR_limit, "input range to pwr()");
}
