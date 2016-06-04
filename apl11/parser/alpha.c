/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "parser.h"
#include "alpha.h"

bool alpha(int s) {
   int c;

   c = s; /* this used to be a mask that destroyed the 8th bit */
   return(
         (c >= 'a' && c <= 'z')
      || (c >= 'A' && c <= 'Z')
      || (litflag == -2 && ( c == '/' || c == '.' ))
   );
}

