/* openAPL, Copyright (C) Branko Bratkovic 1998
 * This file is free software and is covered by the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 *
 * For more details see the GNU General Public License (GPL) in
 * the docs directory.
 */

#include <stdio.h>
#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"

void outputPrintP() {
    printf("digits %d\n", PrintP);
}

void updatePrintP(item_t *p) {
    int i;

    if (p->itemType != DA)
        error(ERR_domain, "assign value not numeric");
    if (p->rank != 0)
        error(ERR_rank, "assign value not scalar");
    i = p->datap[0];
    if (i < 1 || i > 20)
        error(ERR_limit, S_QUAD_ASCII "pp range is 1 to 20");
    PrintP = i;
}

item_t* ex_qpp(io) int io; /* 0 = source, 1 = sink */
{
    item_t* p;

    if (io == 0) {
        p = newdat(DA, 0, 1);
        p->datap[0] = PrintP;
        return (p);
    }
    else {
        pop();
        p = fetch1();
        updatePrintP(p);
        expr_stack_ptr[-1] = (item_t*)p;
        return (0);
    };
}
