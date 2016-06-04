/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

void aplfree(int *ap) {
   struct memblock *item, *last;

   if (ap == 0) return;

   last = 0;
   for (item=firstblock; item; item=item->next) {
      if (item->block == ap) {
         if (last) last->next = item->next;
         else firstblock = item->next;

         if (mem_trace) {
            printf("[aplfree: %d bytes at %XH (data)",
            item->nbytes, item->block);
         }
         free(item->block);

         if (mem_trace) {
            printf(", %d bytes at %XH (memblock)]\n",
            sizeof(struct memblock), item);
         }
         free(item);
         return;
      }
      last = item;
   }
   printf("aplfree bad block address %XH\n", ap);
}

