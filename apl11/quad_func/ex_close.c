/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "utility.h"

void ex_close() {
   SECURITY_CHECK;
   iodone(close(topfix()));
}
