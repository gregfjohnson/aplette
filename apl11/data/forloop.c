/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

forloop(co, arg)
int (*co)();
{
   int i;

   if (idx.size == 0) return;
   if (idx.rank == 0) {
      (*co)(arg);
      return;
   }
   i = 0;
   while (1) {
      while(i < idx.rank) idx.idx[i++] = 0;
      (*co)(arg);
      while (1) {
         idx.idx[i-1]++;
         if (idx.idx[i-1] < idx.dim[i-1]) break;
         i--;
         if (i <= 0) return;
      }
   }
}

