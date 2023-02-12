/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "work_space.h"

void ex_ap()
{
    int fd;
    item_t* p;

    SECURITY_CHECK;
    fd = topfix();
    p = fetch1();
    lseek(fd, 0L, SEEK_END);
    fappend(fd, p);
    if (p->rank == 1)
        writeErrorOnFailure(fd, "\n", 1);
    pop();
    *expr_stack_ptr++ = newdat(DA, 1, 0);
}
