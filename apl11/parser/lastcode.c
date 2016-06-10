/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "opt_codes.h"

int lastCode(char *s) {
   int code, j, last;

   code = 0;
   last = 0;
loop:
   if (code && code != EOL && code != END) last = code;
   code = *s++;
   //if(code != END) code &= 0377;
   switch(code) {

      case EOL:
      if(*s != EOL) break;
      case END:
      return last;

      case QUOT:
      j = *s++;
      s += j;
      break;

      case CONST:
      j = *s++;
      s += j*SDAT;
      break;

      case NAME:
      case FUN:
      case ARG1:
      case ARG2:
      case AUTO:
      case REST:
      case RVAL:
      s += SINT;
      break;

      case INDEX:
      case IMMED:
      s++;
      break;
   }
   goto loop;
}
