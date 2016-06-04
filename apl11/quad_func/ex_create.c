/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include "utility.h"

char *iofname();

ex_creat()
{
   int m;

   SECURITY_CHECK;
   m = topfix();
   iodone(creat(iofname(), m));
}

