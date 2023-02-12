/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "memory.h"

void ex_read()
{
    item_t *p, *q;
    int fd, nb, c;

    SECURITY_CHECK;
    fd = topfix();
    nb = topfix();
    p = newdat(CH, 1, nb);
    c = read(fd, p->datap, nb);
    if (c != nb) {
        q = p;
        if (c <= 0)
            p = newdat(CH, 1, 0);
        else {
            p = newdat(CH, 1, c);
            copy(CH, (char*)q->datap, (char*)p->datap, c);
        }
        aplfree(q);
    }
    *expr_stack_ptr++ = p;
}
