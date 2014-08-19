/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"

ex_arg1()
{
   struct item *p;
   struct nlist *np;

   gsip->ptr += copy(IN, gsip->ptr, &np, 1);
   p = fetch1();
   sp[-1] = np->itemp;
   np->itemp = p;
   np->use = DA;
}

