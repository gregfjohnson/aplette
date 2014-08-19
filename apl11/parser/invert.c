/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "parser.h"
invert(a, b)
{
   flop(a, b);
   flop(b, ccharp);
   flop(a, ccharp);
}

flop(a, b)
char *a, *b;
{
   char *a1, *a2;
   int c;

   a1 = a;
   a2 = b;
   while(a1 < a2) {
      c = *a1;
      *a1++ = *--a2;
      *a2 = c;
   }
}

