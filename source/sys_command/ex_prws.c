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
    item_t* ip;
    int i;

    printf(S_QUAD_ASCII "io " S_LEFTARROW " %d\n", iorigin);
    printf(S_QUAD_ASCII "pw " S_LEFTARROW " %d\n", pagewidth);
    printf(S_QUAD_ASCII "pp " S_LEFTARROW " %d\n", PrintP);

    symtabIterateInit();
    while ((np = symtabIterate()) != NULL) {
        switch (np->entryUse) {
        case CH:
        case DA:
            printf("%s " S_LEFTARROW " ", np->namep);
            ip = np->itemp;
            if (ip->rank) {
                for (i = 0; i < ip->rank; i++)
                    printf("%d ", ip->dim[i]);
                printf(S_RHO "\n");
            }
            *expr_stack_ptr++ = (item_t*)np;
            ex_print();
            pop();
            putchar('\n');
            break;

        case NF:
        case MF:
        case DF:
            *expr_stack_ptr++ = (item_t*)np;
            ex_list();
            putchar('\n');
            break;

        default:
            break;
        }
    }
}
