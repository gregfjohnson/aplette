/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <signal.h>

#include "apl.h"
#include "utility.h"

void ex_signl() {
   int i,j;

   i = topfix();
   j = topfix() != 0;
   iodone(signal(i, (void (*)(int))j) == SIG_ERR ? -1 : 0);
}
