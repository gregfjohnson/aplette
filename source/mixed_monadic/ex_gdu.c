/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "gd.h"

int gdu(const int* p1, const int* p2);

void ex_gdu()
{
    item_t* p;

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
    item_t* p;
    data d1, d2;

    p = expr_stack_ptr[-2];
    p->index = integ + *p1 * idx.delk;
    d1 = getdat(p);
    p->index = integ + *p2 * idx.delk;
    d2 = getdat(p);
    if (fuzz(d1, d2) != 0) {
        if (d1 > d2)
            return (1);
        return (-1);
    }
    return (*p1 - *p2);
}
