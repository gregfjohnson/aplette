/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>
#include "apl.h"
#include "utility.h"
#include "memory.h"
#include "debug.h"

void pop() {
    item_t* p;

    if (stack_trace) {
        printf("pop expr_stack..\n");
    }

    if (expr_stack_ptr <= expr_stack) {
        error(ERR_botch, "pop - expr_stack underflow");
    }
    p = expr_stack_ptr[-1];
    if (p) {
        switch (p->itemType) {
        default:
            printf("[bad type: %s]\n", ItemType_str(p->itemType));
            error(ERR_botch, "pop - unrecognised type");
            break;

        case LBL:
            ((SymTabEntry*)p)->entryUse = UNKNOWN; /* delete label */

        case UNKNOWN:
        case LV:
            break;

        case DA:
        case CH:
            aplfree(p->datap);
            aplfree(p);
            break;

        // case QQ:
        // case QD:
        case EL:
        case NIL:
        case QX:
        case QV:
            aplfree(p);
        }
    }
    expr_stack_ptr--;
}
