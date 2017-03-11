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

struct item* ex_qct(io) int io; /* 0 = source, 1 = sink */
{
    struct item* p;
    data f;

    if (io == 0) {
        p = newdat(DA, 0, 1);
        p->datap[0] = tolerance;
        return (p);
    }
    else {
        pop();
        p = fetch1();

        if (p->itemType != DA)
            error(ERR_domain, "assign value not numeric");

        if (p->rank != 0)
            error(ERR_rank, "assign value not scalar");

        f = p->datap[0];
        if (f < 0)
            f = -f;
        tolerance = f;
        sp[-1] = (struct item*)p;
        return (0);
    };
}
