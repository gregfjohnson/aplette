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
#include "main.h"

item_t* ex_qargv(io) int io; /* 0 = source, 1 = sink */
{
    item_t* p;
    int i;
    int row, col;
    char* n;

    if (io == 0) {
        int max_len = 0;
        for (i = gbl_optind; i < gbl_argc; ++i) {
            int len = strlen(gbl_argv[i]);
            if (max_len < len) max_len = len;
        }

        p = newdat(CH, 2, (gbl_argc - gbl_optind) * max_len);
        n = (char*)p->datap;
        p->dim[0] = gbl_argc - gbl_optind;
        p->dim[1] = max_len;

        for (row = 0; row < gbl_argc - gbl_optind; ++row) {
            int argv_ind = row + gbl_optind;
            int len = strlen(gbl_argv[argv_ind]);
            for (col = 0; col < len; ++col) {
                *n++ = gbl_argv[argv_ind][col];
            }
            for (col = len; col < max_len; ++col) {
                *n++ = ' ';
            }
        }
        return (p);
    }
    else {
        error(ERR_implicit, "cannot change " S_QUAD_ASCII "argv");
    };
    return (0);
}
