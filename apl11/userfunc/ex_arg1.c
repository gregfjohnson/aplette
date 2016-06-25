/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"

void ex_arg1() {
   struct item *p;
   SymTabEntry *np;

   gsip->ptr += copy(IN, (char *) gsip->ptr, (char *) &np, 1);
   p = fetch1();
   sp[-1] = np->itemp;
   np->itemp = p;
   np->use = DA;
}
