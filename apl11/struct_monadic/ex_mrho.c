/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

ex_mrho()
{
   struct item *p, *q;
   data *dp;
   int i;

   p = fetch1();
   q = newdat(DA, 1, p->rank);
   dp = q->datap;
   for(i=0; i<p->rank; i++) *dp++ = p->dim[i];
   pop();
   *sp++ = q;
}

