/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "oper_dyadic.h"

/*
 *   parser generates the following for each  label
 *
 *   AUTO-name  CONST  NAME-name  LABEL
 *
 *   (where CONST is the label address)
 */

void ex_label() {
    SymTabEntry* n;

    ex_asgn();
    n = (SymTabEntry*)sp[-1];

    // lock out assignments
    n->itemp->itemType = LBL;

    sp--;
}
