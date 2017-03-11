/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <signal.h>
typedef void (sighandler_t)(int);

#include "apl.h"
#include "utility.h"

void ex_signl()
{
    int i, j;

    i = topfix();
    j = topfix();

    if (j == 0) {
        iodone(signal(i, SIG_DFL) == SIG_ERR ? -1 : 0);

    } else if (j == 1) {
        iodone(signal(i, SIG_IGN) == SIG_ERR ? -1 : 0);

    } else {
        error(ERR_domain, "signal");
    }
}
