/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "utility.h"

void ex_fork()
{
    int pid;

    SECURITY_CHECK;
    if ((pid = fork()) == -1)
        error(ERR, "could not fork");
    pop();
    iodone(pid);
}
