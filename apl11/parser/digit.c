/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "parser.h"

int digit(s) {
   int c;

   c = s;
   if(c >='0' && c <= '9') return(1);
   return(0);
}

int isodigit(int c) {
   if (c < '0') return 0;
   if (c > '7') return 0;
   return 1;
}
