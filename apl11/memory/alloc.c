/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <stdlib.h>
#include "apl.h"
#include "memory.h"

int * alloc(nbytes)
unsigned nbytes;
{
   struct memblock *newblock;

   if (nbytes <= 0) return 0;
   newblock = (struct memblock *)malloc(sizeof(struct memblock));
   if (newblock == 0) goto failed;
   if (mem_trace) {
      printf("[alloc: %d bytes at %XH (memblock)",
      sizeof(struct memblock), newblock);
   }
   newblock->nbytes = nbytes;
   newblock->block = malloc(nbytes);
   if (newblock->block == 0) goto failed;
   if (mem_trace) {
      printf(", %d bytes at %XH (data)]\n",
      nbytes, newblock->block);
   }
   newblock->next = firstblock;
   firstblock = newblock;
   return newblock->block;

failed:
   printf("Unable to obtain requested memory\n");
   printf("%d bytes were requested\n", nbytes);
   error(ERR_interrupt,"");
   //mem_dump();
   //abort();
}

