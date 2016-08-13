/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <fcntl.h>
#include <unistd.h>
#include "apl.h"
#include "utility.h"
#include "userfunc.h"

int funread(char* fname) {
    struct item* p;
    int f;

    p = sp[-1];
    sp--;

    if (p->itemType != LV) { error(ERR_value, "not a local variable"); }

    if (fname == 0) {
        fname = ((SymTabEntry*)p)->namep;
    }

    f = opn(fname, O_RDONLY);

    fundef(f);

    close(f);

    return f;
}
