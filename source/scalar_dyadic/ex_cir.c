/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include <math.h>

data
    ex_cir(d1, d2)
        data d1,
    d2;
{
    double f, f1;

    switch (fix(d1)) {

    default:
        error(ERR_implicit, "range for circular functions is -7 to +7");

    case -7:
        /* arc tanh */
        f = d2;
        //if(f <= -1. || f >= 1.) error(ERR_limit,"range for arc tanh is -1 to +1");
        if (f < -1. || f > 1.)
            error(ERR_limit, "range for arc tanh is -1 to +1");
        f = log((1. + f) / (1. - f)) / 2.;
        goto ret;

    case -6:
        /* arc cosh */
        f = d2;
        if (f < 1.)
            error(ERR_limit, "range limit for arc cosh is 1");
        f = log(f + sqrt(f * f - 1.));
        goto ret;

    case -5:
        /* arc sinh */
        f = d2;
        f = log(f + sqrt(f * f + 1.));
        goto ret;

    case -4:
        /* sqrt(-1 + x*x) */
        f = -one + d2 * d2;
        goto sq;

    case -3:
        /* arc tan */
        f = d2;
        f = atan(f);
        goto ret;

    case -2:
        /* arc cos */
        f = d2;
        if (f < -1. || f > 1.)
            error(ERR_limit, "range for arc cos is -1 to +1");
        f = atan2(sqrt(1. - f * f), f);
        goto ret;

    case -1:
        /* arc sin */
        f = d2;
        if (f < -1. || f > 1.)
            error(ERR_limit, "range for arc sin is -1 to +1");
        f = atan2(f, sqrt(1. - f * f));
        goto ret;

    case 0:
        /* sqrt(1 - x*x) */
        f = one - d2 * d2;
        goto sq;

    case 1:
        /* sin */
        f = d2;
        f = sin(f);
        goto ret;

    case 2:
        /* cos */
        f = d2;
        f = cos(f);
        goto ret;

    case 3:
        /* tan */
        f = d2;
        f1 = cos(f);
        if (f1 == 0.)
            f = exp(MAXEXP);
        else
            f = sin(f) / f1;
        goto ret;

    case 4:
        /* sqrt(1 + x*x) */
        f = one + d2 * d2;
        goto sq;

    case 5:
        /* sinh */
        f = d2;
        if (f < -MAXEXP || f > MAXEXP)
            error(ERR_limit, "input range overflow");
        f = exp(f);
        f = (f - 1. / f) / 2.;
        goto ret;

    case 6:
        /* cosh */
        f = d2;
        if (f < -MAXEXP || f > MAXEXP)
            error(ERR_limit, "input range overflow");
        f = exp(f);
        f = (f + 1. / f) / 2.;
        goto ret;

    case 7:
        /* tanh */
        f = d2;
        if (f > MAXEXP) {
            f = 1.;
            goto ret;
        }
        if (f < -MAXEXP) {
            f = -1.;
            goto ret;
        }
        f = exp(f);
        f = (f - 1. / f) / (f + 1. / f);
        goto ret;
    }

sq:
    if (f < 0.)
        error(ERR_implicit, "panic - square root of negative number");
    f = sqrt(f);

ret:
    d1 = f;
    return (d1);
}
