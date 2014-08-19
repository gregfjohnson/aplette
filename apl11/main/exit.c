/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <signal.h>
#include <stdio.h>
#include "apl.h"

Exit(s)
{

   int j;

   for(j=3; j<NFDS; j++) close(j);      /* Close files */
   unlink(WSFILE);                  /* Unlink temporaries */
   unlink(scr_file);
   normalExit = 1;                  /* Set this flag */
   exit(s);                     /* And we're outa here */
}
