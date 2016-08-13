/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
static char b[200];

char* iofname(int m)
{
    struct item* p;

    p = fetch1();
    if (p->itemType != CH || p->rank > 1)
        error(ERR_implicit, "file name");
    copy(CH, (char*)p->datap, (char*)b, p->size);
    b[p->size] = 0;
    pop();
    return (b);
}
