/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"
#include "mixed_dyadic.h"

void ex_br()
{
    item_t* p;

    p = fetch1();
    if (p->size == 0)
        return;
    state_indicator_ptr->funlc = fix(getdat(p));
}

void ex_br0()
{
    state_indicator_ptr->funlc = 0;
    ex_elid();
}
