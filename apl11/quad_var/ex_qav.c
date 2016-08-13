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
#include "utility.h"
#include "data.h"
#include "char.h"

struct item* ex_qav(io) int io; /* 0 = source, 1 = sink */
{
    struct item* p;
    int i;
    char* n;

    if (io == 0) {
        p = newdat(CH, 1, 256);
        n = (char*)p->datap;
        for (i = 0; i < p->size; i++) {
            *n = i;
            n++;
        }
        return (p);
    }
    else {
        error(ERR_implicit, "cannot change " S_QUAD "av");
    };
}
