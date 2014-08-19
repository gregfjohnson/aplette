/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"

ex_kill()
{
   int pid, signo;

   SECURITY_CHECK;
   pid = topfix();
   signo = topfix();
   kill(pid, signo);
   *sp++ = newdat(DA, 1, 0);
}

