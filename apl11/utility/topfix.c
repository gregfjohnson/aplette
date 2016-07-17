/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"
#include "data.h"

int topfix()
{
    struct item* p;
    int i;

    p = fetch1();
    if (p->type != DA)
        error(ERR_domain, "topval");
    if (p->size != 1)
        error(ERR_length, "topval");
    i = fix(p->datap[0]);
    pop();
    return (i);
}
