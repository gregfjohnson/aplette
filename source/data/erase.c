/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "memory.h"
#include "utility.h"

void erase(SymTabEntry* np)
{
    int i;

    if (np) {
        switch (np->entryUse) {
        case CH:
        case DA:
        case EL:
        case QV:
        case NIL:
            aplfree((int*)np->itemp->datap);
            aplfree((int*)np->itemp);
            np->itemp = 0;
            break;

        case NF:
        case MF:
        case DF:
            // free the p-code that np points to.
            for (i = 0; i < np->functionLineLength; ++i) {
                aplfree((int*)np->functionLines[i]);
            }
            if (np->functionLines != NULL) {
                aplfree((int*)np->functionLines);
            }

            np->functionLines = NULL;
            np->functionLineCount = 0;
            np->functionLineLength = 0;
        }
        np->entryUse = UNKNOWN;
    }
}
