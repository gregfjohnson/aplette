/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <limits.h>
#include <stdlib.h>

#include "apl.h"
#include "utility.h"
#include "data.h"

void ex_deal()
{
    item_t* p;
    int m, n;
    double f;
    data d1, d2;

    m = topfix();
    n = topfix();
    if (m < 0 || m > n)
        error(ERR_length, "");
    p = newdat(DA, 1, m);
    datum = iorigin;
    for (; n != 0; n--) {
        f = m;
        f /= n;
        if (random() / (float)INT_MAX < f) {
            putdat(p, datum);
            m--;
        }
        datum += one;
    }
    m = p->size;
    while (m > 0) {
        f = random() / (float)INT_MAX;
        n = m * f;
        m--;
        if (n != m) {
            p->index = n;
            d1 = getdat(p);
            p->index = m;
            d2 = getdat(p);
            p->index = n;
            putdat(p, d2);
            p->index = m;
            putdat(p, d1);
        }
    }
    *expr_stack_ptr++ = p;
}
