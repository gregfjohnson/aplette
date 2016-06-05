/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <fcntl.h>

#include "apl.h"
#include "utility.h"

char *iofname();

void ex_open() {
   struct item *p;
   int m;

   m = topfix();
   SECURITY_CHECK;
   iodone(open(iofname(), m));
}
