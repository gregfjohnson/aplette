/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "memory.h"

void erase(struct nlist *np) {
    int *p;
    struct item *itemp;

    p = (int *)np->itemp;
    itemp = np->itemp;
    if(p) {
        switch(np->use) {
        case CH:
        case DA:
            aplfree((int *) itemp->datap);
            break;

        case NF:
        case MF:
        case DF:
            /* free the p-code that p[] points to. 
             * p[0] is size of p minus 1, refer funcomp()
             */
            for((*p)++; *p>0; (*p)--) aplfree((int *) p[*p]);
        }
        aplfree((int *) p);
        np->itemp = 0;
    }
    np->use = 0;
}

