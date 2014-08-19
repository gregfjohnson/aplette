/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"

ex_auto()
{
   struct nlist *np;

   gsip->ptr += copy(IN, gsip->ptr, &np, 1);
   checksp();
   *sp++ = np->itemp;
   np->itemp = 0;
   np->use = 0;
}

