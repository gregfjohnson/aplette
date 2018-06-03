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
#include "format.h"
#include "data.h"
#include "main.h"

/* Print literals */
int lt_print(struct item* p)
{
    int i, j;

    bidx(p);

    for (i = 1; i < p->size; i++) {
        if (intflg)
            break;
        j = getdat(p);
        putAplTouchtypeChar(j);
        column++;
        if (column >= pagewidth) {
            putchar('\n');
            column = 0;
        }

        /* has end of dimension been reached? */
        if (i != p->size) {
            for (j = p->rank - 2; j >= 0; j--) {
                if (i % idx.del[j] == 0) {
                    putchar('\n');
                    column = 0;
                }
            }
        }
    }

    j = getdat(p);
    putAplTouchtypeChar(j);
    column++;
    if (column >= pagewidth) {
        putchar('\n');
        column = 0;
    }
    return (1);
}
