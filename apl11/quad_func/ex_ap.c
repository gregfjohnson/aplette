/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include "utility.h"

ex_ap()
{
   int i, fd;
   struct item *p;

   SECURITY_CHECK;
   fd = topfix();
   p = fetch1();
   lseek(fd, 0L, 2);
   fappend(fd, p);
   if(p->rank == 1) write(fd, "\n", 1);
   pop();
   *sp++ = newdat(DA, 1, 0);
}

