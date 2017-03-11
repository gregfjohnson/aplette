/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"

void ex_nl()
{

    struct item* ip;
    SymTabEntry* np;
    data* dp;
    char *cp, *cp2, tlist[NTYPES];
    int i, count, maxlen;

    /* Namelist quad function.  This is monadic (dyadic not
    * implemented).  The argument is a list of types:
    *  1:   labels
    *  2:   variables
    *  3:   functions
    * whose names are desired.  The result is a character array
    * containing all defined names (in no particular order) of
    * the specified type(s).  The number of rows in the matrix
    * is the number of names; the number of columns is the
    * same as the longest name (other names are space-filled).
    */

    ip = fetch1();
    if (ip->rank > 1)
        error(ERR_rank, "");
    if (ip->itemType != DA)
        error(ERR_domain, "");

    for (i = 0; i < NTYPES; i++)
        tlist[i] = 0;

    for (dp = ip->datap; dp < ip->datap + ip->size; dp++) {
        switch ((int)*dp) {
        case 1:
            tlist[LBL] = 1;
            break;
        case 2:
            tlist[CH] = tlist[DA] = 1;
            break;
        case 3:
            tlist[NF] = tlist[MF] = tlist[DF] = 1;
            break;
        default:
            error(ERR_botch, "");
            break;
        }
    }

    count = maxlen = 0;
    symtabIterateInit();
    while (np = symtabIterate()) {
        // for(np=symbolTable; np < &symbolTable[SYM_TAB_MAX]; np++){
        if (np->entryUse < NTYPES && tlist[np->entryUse]) {
            count++;
            if ((i = strlen(np->namep)) > maxlen)
                maxlen = i;
        }
    }

    ip = newdat(CH, 2, count * maxlen);
    ip->dim[0] = count;
    ip->dim[1] = maxlen;
    cp = ip->datap;

    symtabIterateInit();
    while (np = symtabIterate()) {
        // for(np=symbolTable; np < &symbolTable[SYM_TAB_MAX]; np++) {
        if (np->entryUse < NTYPES && tlist[np->entryUse]) {
            for (cp2 = &np->namep[i = 0]; i < maxlen; i++) {
                if (*cp2)
                    *cp++ = *cp2++;
                else
                    *cp++ = ' ';
            }
        }
    }

    pop();
    *sp++ = ip;
}
