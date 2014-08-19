/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"

ex_br()
{
   struct item *p;

   p = fetch1();
   if(p->size == 0) return;
   gsip->funlc = fix(getdat(p));
}

