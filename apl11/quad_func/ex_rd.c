/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
 
#include "apl.h"
#include "char.h"

ex_rd()
{
   /* note:
    * an empty line is converted to NULL.
    * no '\n' chars are returned.
    */
   char buf[200];
   struct item *p;
   int fd, i;

   SECURITY_CHECK;
   fd = topfix();
   i = 0;
   while((read(fd, &buf[i], 1) == 1) && i < 200 && buf[i] != '\n') i++;
   if(i == 200) error(ERR_limit,"input buffer overflow");
   if(i > 0){
      p = newdat(CH, 1, i);
      copy(CH, buf, p->datap, i);
   }
   else p = newdat(CH, 1, 0);
   *sp++ = p;
}

