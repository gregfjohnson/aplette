/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "apl.h"

char *bad_fn  = "apl.badfn";

int badfnsv(char *fname) {
   /* This routine saves the contents of "fname" in the file
    * named in "bad_fn".  It is called by "funedit" if the
    * header of a function just read in is messed up (thus,
    * the entire file is not lost).  Returns 1 if successful,
    * 0 if not.
    */

   int fd1, fd2, len;
   char buf[512];

   if ((fd1=open(fname, 0)) < 0 || (fd2=creat(bad_fn, 0644)) < 0) return(0);
   while((len=read(fd1, buf, 512)) > 0) write(fd2, buf, len);
   close(fd1);
   close(fd2);
   return(1);
}
