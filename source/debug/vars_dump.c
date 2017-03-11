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

#include <inttypes.h>
#include "apl.h"
#include "data.h"

void vars_dump()
{
    SymTabEntry* n;

    symtabIterateInit();

    while (n = symtabIterate()) {
        // for(n=symbolTable; n->namep; n++) {
        printf("%x:", (uintptr_t)n);
        printf(" namep=%s", n->namep);
        printf(" itemp=%x", (uintptr_t)n->itemp);
        printf(" use=%d", n->entryUse);
        printf(" entryType=%d", n->entryType);
        /*      printf(" label=%d",n->label); */
        printf("\n");
    }
}
