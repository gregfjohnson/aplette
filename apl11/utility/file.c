/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>
#include "apl.h"

opn(file, rw)
char file[];
{
   int fd, (*p)();
   char f2[100];
   extern open(), creat();

   p = (rw > 2 ? creat : open);
   if((fd = (*p)(file,rw)) < 0){
      for(fd=0; fd<13; fd++) f2[fd] = "/usr/lib/apl/"[fd];
      for(fd=0; file[fd]; fd++) f2[fd+13] = file[fd];
      f2[fd+13] = 0;
      if((fd = (*p)(f2, rw)) >= 0){
         printf("[using %s]\n", f2);
         return(fd);
      }
      printf("can't open file %s\n", file);
      error(ERR,"");
   }
   return(fd);
}


empty(fd){

   struct stat sbuf;
   struct fds *fp;

   /* Simulate the Rand Corp.'s "empty" system call on a
    * V7 system by seeing if the given fd is a pipe, and if
    * so, whether or not it is empty.
    */

   if (fstat(fd, &sbuf) < 0) return(-1);      /* Can't "stat" it */
   return(sbuf.st_size == 0);
}
