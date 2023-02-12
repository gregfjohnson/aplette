/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"
#include "data.h"

void ex_miot()
{
    item_t* p;
    data* dp;
    int i;

    i = topfix();
    if (i < 0) { /* must allocate something to ")sic" properly */
        *expr_stack_ptr++ = newdat(DA, 1, 0);
        error(ERR_domain, "right value is less than 0");
    }
    p = newdat(DA, 1, i);
    dp = p->datap;
    datum = iorigin;
    for (; i; i--) {
        *dp++ = datum;
        datum += one;
    }
    *expr_stack_ptr++ = p;
}
