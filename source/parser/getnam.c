/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "memory.h"
#include "utility.h"
#include "local_parser.h"
#include "data.h"
#include "userfunc.h"
#include "debug.h"
#include "y.tab.h"

// #define DEBUG

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

    #ifdef DEBUG
        printf("yo from getnam.  context:  %d; name:  '%s'\n",
               (int) context, name);
        printf("\ncurrent symbol table:\n");
        vars_dump();
    #endif

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
        SymTabEntry* newSymTabEntry;

        if (context == compile_function_defn
            || context == compile_function_prolog
            || context == compile_function_epilog)
        {
            newSymTabEntry = symtabEntryCreate(name);

            #ifdef DEBUG
                printf("getnam; found np %p; created new symtab entry %p for '%s'\n",
                        np, (void *) newSymTabEntry, name);
            #endif

        } else {
            newSymTabEntry = np;

            #ifdef DEBUG
                printf("getnam; found np %p for '%s'; using it..\n", np, name);
            #endif
        }

        lv.charptr = (char*) newSymTabEntry;

        switch (np->entryUse) {
        case NF:
            if (context == compile_function_defn)
                sichk(np);

            return (nfun);

        case MF:
            if (context == compile_function_defn)
                sichk(np);

            return (mfun);

        case DF:
            if (context == compile_function_defn)
                sichk(np);

            return (dfun);

        default:
            return (nam);
        }
    }

    np = symtabEntryCreate(name);

    #ifdef DEBUG
        printf("getnam; did not find np; created new symtab entry %p for '%s'\n",
                (void *) np, name);
    #endif

    np->itemType = LV;
    lv.charptr = (char *) np;

    return nam;
}
