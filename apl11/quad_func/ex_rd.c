/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>
 
#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"

void ex_rd() {
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
      copy(CH, (char *) buf, (char *) p->datap, i);
   }
   else p = newdat(CH, 1, 0);
   *sp++ = p;
}
