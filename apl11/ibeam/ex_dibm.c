/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "utility.h"

void ex_dibm() {
   int arg;
   struct item *p;

   /* Dyadic i-beam functions.  I-beam 63 assumes that the
    * "empty" system call (check whether pipe empty) has been
    * implemented in the Unix kernel.
    */

   arg = topfix();               /* Get left argument */

   switch(topfix()) {

   default:
      error(ERR_implicit,"unknown i-beam");

   case 34:                   /* "Nice" system call */
      datum = nice(arg);
      break;

   case 35:                  /* "Sleep" system call */
      datum = sleep(arg);
      break;

   case 63:                  /* "Empty" system call */
      datum = empty(arg);
      break;

   }

   p = newdat(DA, 0, 1);
   p->datap[0] = datum;
   *sp++ = p;
}
