/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <unistd.h>

#include "apl.h"
#include "utility.h"
#include "fdat.h"
#include "work_space.h"
#include "data.h"

static int nsave(int ffile, SymTabEntry* an);
static void saveWorkspaceInformation(int ffile);

void wssave(int ffile) {
    SymTabEntry* n;

    saveWorkspaceInformation(ffile);

    symtabIterateInit();
    while (n = symtabIterate()) {
        nsave(ffile, n);
    }

    fdat(ffile);
    close(ffile);
}

static void saveWorkspaceInformation(int ffile) {
    char buffer[64];
    writeErrorOnFailure(ffile, "apl\\11\n", 7);

    sprintf(buffer, "tolerance %lg\n", tolerance);
    writeErrorOnFailure(ffile, buffer, strlen(buffer));

    sprintf(buffer, "origin %d\n", iorigin);
    writeErrorOnFailure(ffile, buffer, strlen(buffer));

    sprintf(buffer, "width %d\n", pagewidth);
    writeErrorOnFailure(ffile, buffer, strlen(buffer));

    sprintf(buffer, "digits %d\n", PrintP);
    writeErrorOnFailure(ffile, buffer, strlen(buffer));
}

static int nsave(int ffile, SymTabEntry* an) {
    char c, buffer[64];
    int i, size;
    struct item* p;

    if (an->entryUse == UNKNOWN || (an->entryUse == DA && an->itemp == 0))
        return 0;

    switch (an->entryUse) {
    default:
        close(ffile);
        error(ERR_botch, "type is unknown");

    case DA:
        p = an->itemp;
        if (p->itemType == DA)
            writeErrorOnFailure(ffile, "DA ", 3);
        else
            writeErrorOnFailure(ffile, "CH ", 3);
        writeErrorOnFailure(ffile, an->namep, strlen(an->namep));
        sprintf(buffer, " %d", p->rank);
        writeErrorOnFailure(ffile, buffer, strlen(buffer));
        size = 1;
        for (i = 0; i < p->rank; i++) {
            sprintf(buffer, " %d", p->dim[i]);
            writeErrorOnFailure(ffile, buffer, strlen(buffer));
            size *= p->dim[i];
        }
        writeErrorOnFailure(ffile, "\n", 1);
        if (p->itemType == DA) {
            data* dp;
            dp = p->datap;
            writeErrorOnFailure(ffile, dp, size * sizeof(data));
        }
        else {
            writeErrorOnFailure(ffile, (char*)p->datap, size);
            writeErrorOnFailure(ffile, "\n", 1);
        }
        break;

    case NF:
        writeErrorOnFailure(ffile, "NF ", 3);
        goto real;

    case MF:
        writeErrorOnFailure(ffile, "MF ", 3);
        goto real;

    case DF:
        writeErrorOnFailure(ffile, "DF ", 3);

    real: {
        char zero = '\0';
        int line, i;
        char lineCount[64];

        // write the function's name on the same line as the function arity
        // printed above..
        writeErrorOnFailure(ffile, an->namep, strlen(an->namep));
        writeErrorOnFailure(ffile, "\n", 1);

        // write the function source code lines..
        for (line = 0; line < an->sourceCodeCount; ++line) {
            for (i = 0; i < strlen(an->functionSourceCode[line])-1; ++i) {
                writeErrorOnFailure(ffile, &an->functionSourceCode[line][i], 1);
            }
        }

        // a zero byte is the marker for end of a function definition.
        writeErrorOnFailure(ffile, &zero, 1);

        break;
    }
    }
    return 0;
}
