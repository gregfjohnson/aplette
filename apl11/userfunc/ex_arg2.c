/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"

void ex_arg2() {
   struct item *p1, *p2;
   SymTabEntry *np1, *np2;

   gsip->ptr += copy(IN, (char *) gsip->ptr, (char *) &np2, 1);   /* get first argument's name */
   gsip->ptr++;                     /* skip over ARG1 */
   gsip->ptr += copy(IN, (char *) gsip->ptr, (char *) &np1, 1);   /* get second arg's name */
   p1 = fetch1();               /* get first expr to be bound to arg */
   p2 = fetch(sp[-2]);            /* get second one */
   sp[-1] = np1->itemp;         /* save old value of name on stack */
   sp[-2] = np2->itemp;         /* save second */
   np1->itemp = p1;            /* new arg1 binding */
   np2->itemp = p2;            /* ditto arg2 */
   np1->use = DA;               /* release safety catch */
   np2->use = DA;
}
