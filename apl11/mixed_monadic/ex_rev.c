/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"

ex_rev0()
{
   fetch1();
   revk(0);
}

ex_revk()
{
   int k;

   k = topfix() - iorigin;
   fetch1();
   revk(k);
}

ex_rev()
{
   struct item *p;

   p = fetch1();
   revk(p->rank-1);
}

revk(k)
{
   int o;

   bidx(sp[-1]);
   if(k < 0 || k >= idx.rank) error(ERR_index,"");
   o = idx.del[k] * (idx.dim[k]-1);
   idx.del[k] = -idx.del[k];
   map(o);
}
