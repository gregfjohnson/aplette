/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

int access() {
   int i, n;

   n = 0;
   for(i=0; i<idx.rank; i++) n += idx.idx[i] * idx.del[i];
   return(n);
}

