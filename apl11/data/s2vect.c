/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

struct item *
s2vect(ap)
struct item *ap;
{
   struct item *p, *q;

   p = ap;
   q = newdat(p->type, 1, 1);
   q->datap = p->datap;
   q->dim[0] = 1;
   return(q);
}

