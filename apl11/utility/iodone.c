/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"

void iodone(int ok) {
   struct item *p;

   p = newdat(DA, 0, 1);
   p->datap[0] = ok;
   *sp++ = p;
}

