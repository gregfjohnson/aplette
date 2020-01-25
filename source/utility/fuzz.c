/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

int fuzz(data c1, data c2)
{
    double f1, f2;
    double d1, d2;

    d1 = creal(c1);
    d2 = creal(c2);

    f1 = d1;
    if (f1 < 0.)
        f1 = -f1;

    f2 = d2;
    if (f2 < 0.)
        f2 = -f2;

    if (f2 > f1)
        f1 = f2;

    f1 *= creal(tolerance);

    if (d1 > d2) {
        if (d2 + f1 >= d1)
            return (0);
        else
            return (1);
    }
    if (d1 + f1 >= d2)
        return (0);
    else
        return (-1);
}
