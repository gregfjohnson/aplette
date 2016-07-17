/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"
#include "data.h"

data
    getdat(ip) struct item* ip;
{
    struct item* p;
    int i;
    data d;

    /* Get the data value stored at index p->index.  If the
    * index is out of range it will be wrapped around.  If
    * the data item is null, a zero or blank will be returned.
    */

    p = ip;
    i = p->index;
    while (i >= p->size) {
        if (p->size == 0)
            return ((p->type == DA) ? zero : (data)' ') /* let the caller beware */;
        i -= p->size;
    }
    if (p->type == DA) {
        d = p->datap[i];
    }
    else if (p->type == CH) {
        d = ((struct chrstrct*)p->datap)->c[i];
    }
    else
        error(ERR_botch, "getdat");
    i++;
    p->index = i;
    return (d);
}
