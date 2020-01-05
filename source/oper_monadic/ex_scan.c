/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <stdint.h>
#include "apl.h"
#include "utility.h"
#include "opt_codes.h"
#include "data.h"

void scan0(int k);
void scan1(data* dataPtr, data (*f)(data, data));

void ex_scn0()
{
    fetch1();
    scan0(0);
}

void ex_scan()
{
    struct item* p;

    p = fetch1();
    scan0(p->rank - 1);
}

void ex_scnk()
{
    int i;

    i = topfix() - iorigin;
    scan0(i);
}

void scan0(int k)
{
    struct item *p, *q;
    data (*fn)(data, data);

    p = fetch1();
    if (p->itemType != DA)
        error(ERR_domain, "not numeric data");

    bidx(p);
    colapse(k);

    if (idx.dimk == 0) {
        /*
	*  scan identities - ets/jrl 5/76
	*/
        q = newdat(DA, 0, 1);
        q->dim[0] = 1;

        switch (*gsip->ptr++) {
        case ADD:
        case SUB:
        case OR:
            q->datap[0] = 0;
            break;

        case AND:
        case MUL:
        case DIV:
            q->datap[0] = 1;
            break;

        case MIN:
            q->datap[0] = 1.0e38;
            break;

        case MAX:
            q->datap[0] = -1.0e38;
            break;

        default:
            error(ERR_implicit, "cannot scan with this function");
        }

        pop();
        *sp++ = q;

        return;
    }

    fn = (data (*)(data, data))exop[(uint32_t) *gsip->ptr++];

    indexIterateInit(&idx);
    while (indexIterate(&idx)) {
        scan1(p->datap, fn);
    }
}

void scan1(data* dataPtr, data (*f)(data, data))
{
    int i, j;
    data *dp, *ip, d;

    for (i = 0; i < idx.dimk; i++) {
        dp = dataPtr + access() + (idx.dimk - (i + 1)) * idx.delk;
        ip = dp;
        d = *ip;

        for (j = 1; j < idx.dimk - i; j++) {
            ip -= idx.delk;
            d = (*f)(*ip, d);
        }

        *dp = d;
    }
}
