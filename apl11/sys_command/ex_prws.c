/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>

#include "apl.h"
#include "data.h"
#include "char.h"
#include "ex_list.h"
#include "print.h"

/* Print Workspace */
void ex_prws()
{
    SymTabEntry* np;
    struct item* ip;
    int i;

    printf(S_QUAD "io " S_LEFTARROW " %d\n", iorigin);
    printf(S_QUAD "pw " S_LEFTARROW " %d\n", pagewidth);
    printf(S_QUAD "pp " S_LEFTARROW " %d\n", PrintP);
    for (np = symbolTable; np < &symbolTable[SYM_TAB_MAX]; np++) {
        switch (np->use) {
        case CH:
        case DA:
            printf("%s " S_LEFTARROW " ", np->namep);
            ip = np->itemp;
            if (ip->rank) {
                for (i = 0; i < ip->rank; i++)
                    printf("%d ", ip->dim[i]);
                printf(S_RHO "\n");
            }
            *sp++ = (struct item*)np;
            ex_print();
            pop();
            putchar('\n');
            break;

        case NF:
        case MF:
        case DF:
            *sp++ = (struct item*)np;
            ex_list();
            putchar('\n');
            break;
        }
    }
}
