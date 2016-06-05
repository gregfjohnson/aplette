/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "opt_codes.h"

void reverse(char *s) {
   char *p, *q, c;
   int j;

   p = q = s;
   while(*p != END) p++;
   p -= 1+sizeof(char *);
   while(q < p){
      for(j=0; j<1+sizeof (char *); j++) {
         c = p[j];
         p[j] = q[j];
         q[j] = c;
      }
      q += j;
      p -= j;
   }
}
