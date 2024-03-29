/* openAPL, Copyright (C) Branko Bratkovic 1999
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

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "format.h"

/* dyadic format */
void ex_dfmt()
{
    item_t *rp, *lp, *q;

    lp = fetch2();
    rp = expr_stack_ptr[-2];

    switch (lp->itemType) {
    case DA:
        break;

    case CH:
        error(ERR_domain, "");
        break;

    default:
        error(ERR_botch, "attempt to format unsupported type");
    }

    switch (rp->itemType) {
    case DA:
        /* convert rp from numeric to a literal array */
        q = fp_dfmt(lp, rp);
        pop();
        pop();
        *expr_stack_ptr++ = q; // put it onto the expr_stack
        break;

    case CH:
        error(ERR_domain, "");
        break;

    default:
        error(ERR_botch, "attempt to format unsupported type");
    }
}
