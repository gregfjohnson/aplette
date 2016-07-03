/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "data.h"
#include "local_parser.h"
#include "debug.h"

char *name(char *np, char c) {
   char *p = ccharp;

   *ccharp++ = c;
   copy(PTR, (char *) &np, ccharp, 1);
   ccharp += SPTR;

    parseDump(oline, ccharp-oline);

   return p;
}

