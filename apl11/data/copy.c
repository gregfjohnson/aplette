/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

int copy(int type, char *from, char *to, int size) {
   int i;
   char *a, *b;
   int s;

   if((i = size) == 0) return(0);
   a = from;
   b = to;
   if(type == DA) i *= SDAT;
   if(type == IN) i *= SINT;
   s = i;
   do
      *b++ = *a++;
   while(--i);
   return(s);
}

