/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"

void ex_write()
{
    int fd, m;
    struct item* p;
    int mult; /* Multiplier (data size) */

    SECURITY_CHECK;
    fd = topfix();
    p = fetch1();
    if (p->type != CH && p->type != DA)
        error(ERR_domain, "");
    mult = p->type == CH ? 1 : sizeof datum;
    m = write(fd, p->datap, p->size * mult) / mult;
    pop();
    iodone(m);
}
