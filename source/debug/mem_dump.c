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

#include <inttypes.h>
#include "memory.h"
#include "apl.h"

void mem_dump()
{
    struct memblock* item;
    printf("Dumping dynamic memory... \n");
    printf("firstblock, points to %p \n", (void *) firstblock);

    if (firstblock == 0) {
        printf("no dynamic memory\n");
        return;
    }
    for (item = firstblock; item; item = item->next) {
        printf("%p points to %d bytes at %p \n",
            (void *)item, item->nbytes, (void *)item->block);
    }
}
