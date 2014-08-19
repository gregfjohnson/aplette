/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

/*
 *   Floating-point initialization and trap service
 *
 */

#include <signal.h>
#include "apl.h"

char *fpelist[] = {
   "floating exception",
   "integer overflow",
   "integer divide by zero",
   "floating overflow",
   "floating divide by zero",
   "floating underflow",
   "decimal overflow",
   "subscript range",
   "floating overflow",
   "floating divide by zero",
   "floating underflow"
};

fpe(signo, param)
unsigned param;
{
   signal(SIGFPE, fpe);
   if (param >= sizeof fpelist/sizeof fpelist[0]) error(ERR,"floating exception");
   else error(ERR,fpelist[param]);
}

fppinit()
{
   signal(SIGFPE, fpe);
}
