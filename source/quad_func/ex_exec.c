/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"

#define MAXP 20

void ex_exec()
{
    item_t* p;
    int i, j;
    char *cp, *argv[MAXP + 1];

    SECURITY_CHECK;
    p = fetch1();
    if (!p->rank || p->rank > 2)
        error(ERR_rank, "");
    if (p->size > 500)
        error(ERR_length, "");
    if (p->itemType != CH)
        error(ERR_domain, "");
    if (p->rank == 2) {
        if (p->dim[0] > MAXP)
            error(ERR_length, "");
        cp = (char*)(p->datap);
        for (i = 0; i < p->dim[0]; i++)
            argv[i] = cp + i * p->dim[1];
        argv[p->dim[0]] = 0;
    }
    else {
        cp = (char*)(p->datap);
        for (i = j = 0; i < MAXP && cp < (char*)(p->datap) + p->size; cp++) {
            if (!*cp)
                j = 0;
            else if (!j) {
                j = 1;
                argv[i++] = (char*)cp;
            }
        }
        if (i == MAXP || *--cp)
            error(ERR, "exec - panic");
        argv[i] = 0;
    }
    execv(argv[0], &argv[1]);
    pop();
    p = newdat(DA, 0, 0);
    *expr_stack_ptr++ = p;
}
