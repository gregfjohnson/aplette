/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "memory.h"
#include "utility.h"
#include "local_parser.h"
#include "data.h"
#include "userfunc.h"
#include "y.tab.h"

extern struct COMM comtab[];
#define lv yylval

int getnam(char ic) {
    char name[NAMS], *cp;
    int c;
    SymTabEntry* np;

    // copy identifier from iline to local variable "name".
    // first character is the arg passed in to getnam(),
    // subsequent chars are from iline, while alpha() or digit().
    c = ic;
    cp = name;
    do {
        if (cp >= &name[NAMS - 1])
            error(ERR_length, "name too long");
        *cp++ = c;
        c = *iline++;
    } while (alpha(c) || digit(c) || c == (int) '_');
    *cp++ = 0;

    iline--;

    // commands
    if (litflag == -1) {
        litflag = -2;
        for (c = 0; comtab[c].ct_name; c++) {
            if (equal(name, comtab[c].ct_name))
                break;
        }
        immedcmd = lv.charval = comtab[c].ct_ylval;
        return (comtab[c].ct_ytype);
    }

    np = symtabFind(name);

    if (np != NULL) {
        lv.charptr = (char*) np;

        switch (np->entryUse) {
        case NF:
            if (context == lex2)
                sichk(np);

            return (nfun);

        case MF:
            if (context == lex2)
                sichk(np);

            return (mfun);

        case DF:
            if (context == lex2)
                sichk(np);

            return (dfun);

        default:
            return (nam);
        }
        return (nam);
    }

    np = symtabEntryCreate(name);

    np->itemType = LV;
    lv.charptr = (char *) np;

    return nam;
}
