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

/* monadic format */
void ex_mfmt()
{
    struct item *p, *q;

    p = fetch1();
    switch (p->itemType) {
    case DA:
        /* convert p from numeric to a literal array */
        q = fp_mfmt(p);
        pop();
        *sp++ = q; // put it onto the stack
        break;

    case CH:
        /* do nothing, pass p unchanged */
        break;

    default:
        error(ERR_botch, "attempt to format unsupported type");
    }
}
