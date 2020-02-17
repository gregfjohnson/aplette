/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"
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
    SymTabEntry* newEntry;

    // create a new symtab entry..
    n = (SymTabEntry*) sp[-1];
    symtabRemoveEntry(n);
    newEntry = symtabInsert(n->namep);
    newEntry->itemType = LV;

    sp[-1] = (struct item *) newEntry;
    ex_asgn();

    // lock out assignments
    newEntry->itemp->itemType = LBL;

    sp--;
}
