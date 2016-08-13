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

int nsave(int ffile, SymTabEntry* an);

void wssave(int ffile)
{
    SymTabEntry* n;

    nsave(ffile, 0);
    symtabIterateInit();
    while (n = symtabIterate()) {
        // for(n=symbolTable; n->namep; n++) {
        nsave(ffile, n);
    }
    fdat(ffile);
    close(ffile);
}

int nsave(int ffile, SymTabEntry* an)
{
    char c, buffer[64];
    int i, size;
    struct item* p;

    if (an == 0) {
        writeErrorOnFailure(ffile, "apl\\11\n", 7);
        sprintf(buffer, "tolerance %lg\n", tolerance);
        writeErrorOnFailure(ffile, buffer, strlen(buffer));
        sprintf(buffer, "origin %d\n", iorigin);
        writeErrorOnFailure(ffile, buffer, strlen(buffer));
        sprintf(buffer, "width %d\n", pagewidth);
        writeErrorOnFailure(ffile, buffer, strlen(buffer));
        sprintf(buffer, "digits %d\n", PrintP);
        writeErrorOnFailure(ffile, buffer, strlen(buffer));
        return 0;
    }

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
        int line, i;
        char lineCount[64];
        unsigned char zero = 0;
        writeErrorOnFailure(ffile, an->namep, strlen(an->namep));
        sprintf(lineCount, " %d", an->sourceCodeCount);
        printf("lineCount:  >>%s<<\n", lineCount);
        writeErrorOnFailure(ffile, lineCount, strlen(lineCount));
        writeErrorOnFailure(ffile, "\n", 1);
        for (line = 0; line < an->sourceCodeCount; ++line) {
            for (i = 0; i < strlen(an->functionSourceCode[line])-1; ++i) {
                // printf("%c", an->functionSourceCode[line][i]);
                writeErrorOnFailure(ffile, &an->functionSourceCode[line][i], 1);
            }
        }
        writeErrorOnFailure(ffile, &zero, 1);
        break;
    }
    }
    return 0;
}
