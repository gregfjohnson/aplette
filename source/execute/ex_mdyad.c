#include "apl.h"
#include "data.h"
#include "utility.h"

/* this routine deals with dyadic scalar functions
 * where one arguments is a single character 
 * and the other is floating point
 * it adjusts the shape of the arguments as required
 */

/* function added by tyl */
void ex_mdyad(data (*f)(), struct item* ap, struct item* ap1)
{
    int i, j;
    struct item *p, *p1, *p2;
    data d;
    int rank, size;

    p = ap;
    p1 = ap1;

    if (p->rank == 0 || p->size == 1) {
        rank = p1->rank;
        size = p1->size;
        j = 1; /* LHS is the single character */
    }
    else if (p1->rank == 0 || p1->size == 1) {
        rank = p->rank;
        size = p->size;
        j = 2; /* RHS is the single character */
    }
    else {
        if (p1->rank != p->rank)
            error(ERR_rank, "mixdyad - arrays do not match");
        for (i = 0; i < p->rank; i++) {
            if (p->dim[i] != p1->dim[i])
                error(ERR_length, "mixdyad - both dimensions are larger than one");
        }
        rank = p->rank;
        size = p->size;
        j = 1; /* LHS is the single character */
    }

    p2 = newdat(DA, rank, size);
    if (j == 1) {
        for (i = 0; i < rank; i++)
            p2->dim[i] = p1->dim[i];
        /* fetch LHS character and convert to float */
        d = ((struct chrstrct*)p->datap)->c[0];
        for (i = 0; i < size; i++) {
            p2->datap[i] = (*f)(d, p1->datap[i]);
        }
    }
    else {
        for (i = 0; i < rank; i++)
            p2->dim[i] = p->dim[i];
        /* fetch RHS character and convert to float */
        d = ((struct chrstrct*)p1->datap)->c[0];
        for (i = 0; i < size; i++) {
            p2->datap[i] = (*f)(p->datap[i], d);
        }
    }
    pop();
    pop();
    *sp++ = p2;
}
