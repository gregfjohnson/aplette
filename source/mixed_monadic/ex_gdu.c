/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include <math.h>
#include "gd.h"

int gdu(const int* p1, const int* p2);

void ex_gdu()
{
    struct item* p;

    p = fetch1();
    gd0(p->rank - 1, (int (*)(const void*, const void*))gdu);
}

void ex_gduk()
{
    int k;

    k = topfix() - iorigin;
    fetch1();
    gd0(k, (int (*)(const void*, const void*))gdu);
}

int gdu(const int* p1, const int* p2)
{
    struct item* p;
    data d1, d2;

    p = sp[-2];
    p->index = integ + *p1 * idx.delk;
    d1 = getdat(p);
    p->index = integ + *p2 * idx.delk;
    d2 = getdat(p);
    if (fabs(cimag(d1)) > creal(tolerance)
        || fabs(cimag(d2)) > creal(tolerance))
    {
        error(ERR_domain, "cannot sort complex values");
    }
    if (fuzz(d1, d2) != 0) {
        if (creal(d1) > creal(d2))
            return (1);
        return (-1);
    }
    return (*p1 - *p2);
}
