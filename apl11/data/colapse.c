/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"

void colapse(int k) {
   int i;

   if(k < 0 || k >= idx.rank) error(ERR_index,"collapse");
   idx.dimk = idx.dim[k];
   idx.delk = idx.del[k];
   for(i=k; i<idx.rank; i++) {
      idx.del[i] = idx.del[i+1];
      idx.dim[i] = idx.dim[i+1];
   }
   if (idx.dimk) idx.size /= idx.dimk;
   idx.rank--;
}

