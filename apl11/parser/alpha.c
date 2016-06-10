/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "local_parser.h"

bool alpha(char s) {
   return(
         (s >= 'a' && s <= 'z')
      || (s >= 'A' && s <= 'Z')
      || (litflag == -2 && ( s == '/' || s == '.' ))
   );
}

