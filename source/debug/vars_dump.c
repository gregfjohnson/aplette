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
#include "debug.h"

void vars_dump()
{
    SymTabEntry* n;

    symtabIterateInit();
    while ((n = symtabIterate()) != NULL) {
        printf("%p:", (void *) n);
        printf(" namep=%s", n->namep);
        printf(" itemp=%p", (void *)n->itemp);
        printf(" use=%s", ItemType_str(n->entryUse));
        printf(" itemType=%s", ItemType_str(n->itemType));
        printf("\n");
    }
}
