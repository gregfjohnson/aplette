/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

ex_print()
{
  if(print()) {	/* print() would only return 0 for type NIL */
     putchar('\n');
     column=0;
  }
  return(0);
}

