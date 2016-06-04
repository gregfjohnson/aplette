/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include "utility.h"

ex_fork()
{
   int pid;
   struct item *p;

   SECURITY_CHECK;
   if ((pid = fork(0)) == -1) error(ERR,"could not fork");
   pop();
   iodone(pid);
}

