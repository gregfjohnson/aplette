/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"

char *iofname();

ex_unlink()
{
   SECURITY_CHECK;
   iodone(unlink(iofname()));
}

