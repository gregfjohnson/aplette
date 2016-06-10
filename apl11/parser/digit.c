/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "local_parser.h"

int digit(char s) {
   if(s >='0' && s <= '9') return(1);
   return(0);
}

int isodigit(char c) {
   if (c < '0') return 0;
   if (c > '7') return 0;
   return 1;
}
