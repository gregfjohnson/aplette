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
#include "utility.h"
#include "format.h"
#include "local_print.h"

int print()
{
    struct item* p;

    p = fetch1();
    if (p->type == NIL)
        return (0);
    if (p->size == 0)
        return (1);
    switch (p->type) {
    case DA:
        fp_print(p);
        break;

    case CH:
        lt_print(p);
        break;

    default:
        error(ERR_botch, "attempt to print unsupported type");
    }
    return (1);
}
