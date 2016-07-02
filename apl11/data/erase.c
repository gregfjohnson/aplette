/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "memory.h"

void erase(SymTabEntry *np) {
    int *p;
    struct item *itemp;
    int i;

    if(p) {
        switch(np->use) {
        case CH:
        case DA:
            p = (int *)np->itemp;
            itemp = np->itemp;
            aplfree((int *) itemp->datap);
            aplfree((int *) p);
            np->itemp = 0;
            break;

        case NF:
        case MF:
        case DF:
            /* free the p-code that p[] points to. 
             * p[0] is size of p minus 1, refer funcomp()
             */
            // for((*p)++; *p>0; (*p)--) aplfree((int *) p[*p]);
            for (i = 0; i < np->functionPcodeLineLength; ++i) {
                aplfree((int *) np->functionPcodeLines[i]);
            }
            aplfree((int *) np->functionPcodeLines);
            np->functionPcodeLines = NULL;
            np->functionLineCount  = 0;
            np->functionPcodeLineLength  = 0;
        }
    }
    np->use = 0;
}

