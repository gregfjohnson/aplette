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

/* Changed 26.9.1999 by tyl */

#include <stdio.h>
#include "apl.h"
#include "data.h"
#include "utility.h"

struct item* ex_qio(io) int io; /* 0 = source, 1 = sink */
{
    struct item* p;
    int i;

    if (io == 0) {
        p = newdat(DA, 0, 1);
        p->datap[0] = iorigin;
        return (p);
    }
    else {
        pop();
        p = fetch1();

        if (p->itemType != DA)
            error(ERR_domain, "assign value not numeric");

        if (p->rank != 0)
            error(ERR_rank, "assign value not scalar");

        i = fix(p->datap[0]);
        if (i == 0 || i == 1)
            iorigin = (data)i;
        else
            error(ERR_domain, "assign value not 0 or 1");
        expr_stack_ptr[-1] = (struct item*)p;
        return (0);
    };
}
