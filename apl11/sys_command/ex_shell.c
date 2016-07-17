/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdlib.h>

#include "apl.h"
#include "utility.h"

/* If the environment variable SHELL is defined, attempt to
* execute that shell.  If not, or if that exec fails, attempt
* to execute the standard shell, /bin/sh
*/
void ex_shell()
{
    char *getenv(), *sh;

    sh = getenv("SHELL");
    if (sh == 0)
        sh = "/bin/sh";
    if (system(sh) == -1)
        error(ERR, "attempt to start shell failed");
}
