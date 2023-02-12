/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <unistd.h>
#include "apl.h"
#include "data.h"
#include "utility.h"
#include "work_space.h"

void fappend(int fd, item_t* ap)
{
    item_t* p;
    char* p1;
    int i, dim0, dim1;
    char b[200];

    p = ap;
    if (p->rank != 2 && p->rank != 1)
        error(ERR_rank, "");
    if (p->itemType != CH)
        error(ERR_domain, "not character type");
    dim1 = p->dim[1];
    dim0 = p->dim[0];
    if (p->rank == 1)
        dim1 = dim0;
    p1 = (char*)(p->datap);
    if (p->rank == 2) {
        for (i = 0; i < dim0; i++) {
            copy(CH, p1, b, dim1);
            p1 += dim1;
            b[dim1] = '\n';
            writeErrorOnFailure(fd, b, dim1 + 1);
        }
    }
    else
        writeErrorOnFailure(fd, p->datap, dim0);
}
