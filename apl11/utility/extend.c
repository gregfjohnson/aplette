/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

/* extend - used by ex_base and ex_iprod */
struct item *
extend(ty, n, d)
data d;
{
   int i;
   struct item *q;

   if(ty != DA) error(ERR_domain,"not numeric type");
   q = newdat(ty, 1, n);
   for(i=0; i<n; i++) q->datap[i] = d;
   return(q);
}
