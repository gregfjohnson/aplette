/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
// #include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "apl.h"

void Exit(int s) {

   int j;

   for(j=3; j<NFDS; j++) close(j);
   unlink(WSFILE);                  /* Unlink temporaries */
   unlink(scr_file);
   normalExit = 1;                  /* Set this flag for atexit() */
   exit(s);                         /* And we're outa here */
}
