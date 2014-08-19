/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "parser.h"
#include "char.h"
#include "y.tab.h"

getnum(ic)
{
   double d1, d2;
   int c, n, n1, s, s1;

   s = 0;
   n = 0;
   d1 = 0.;
   c = ic;
   if(c == C_OVERBAR) {		/* C_OVERBAR is negative number prefix */
      s++;
      c = *iline++;
   }
   while(digit(c)) {
      d1 = d1*10. + c - '0';
      c = *iline++;
   }
   if(c == '.') {
      c = *iline++;
      while(digit(c)) {
         d1 = d1*10. + c - '0';
         c = *iline++;
         n--;
      }
   }
   if(c == 'e' || c == 'E') {
      s1 = 0;
      n1 = 0;
      c = *iline++;
      if(c == C_OVERBAR) {	/* C_OVERBAR is negative number prefix */
         s1++;
         c = *iline++;
      }
      while(digit(c)) {
         n1 = n1*10 + c - '0';
         c = *iline++;
      }
      if(s1) n -= n1;
      else n += n1;
   }
   n1 = n;
   if(n1 < 0) n1 = -n1;
   d2 = 1.;
   while(n1--) d2 *= 10.;
   if(n < 0) d1 /= d2;
   else d1 *= d2;
   if(s) d1 = -d1;
   iline--;
   datum = d1;
   return(numb);
}

