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

#include "memory.h"
#include "apl.h"

mem_dump()
{
   struct memblock *item;
   printf("Dumping dynamic memory... \n");
   printf("firstblock, points to %X \n", firstblock );

   if (firstblock == 0) {
      printf("no dynamic memory\n");
      return;
   }
   for (item=firstblock; item; item=item->next) {
      printf("%XH points to %d bytes at %XH \n", 
              item,     item->nbytes, item->block);
   }
}
