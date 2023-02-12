/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"

void putdat(item_t* ip, data d)
{
    item_t* p;
    int i;

    p = ip;
    i = p->index;
    if (i >= p->size)
        error(ERR_botch, "putdat - index exceeds size");
    if (p->itemType == DA) {
        p->datap[i] = d;
    }
    else if (p->itemType == CH) {
        ((struct chrstrct*)p->datap)->c[i] = d;
    }
    else
        error(ERR_botch, "putdat - unrecognised type");
    i++;
    p->index = i;
}
