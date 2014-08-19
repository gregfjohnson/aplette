/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include <signal.h>

ex_signl()
{
   int i,j;

   i = topfix();
   j = topfix() != 0;
   iodone((int)signal(i,(int (*)())j));
}

