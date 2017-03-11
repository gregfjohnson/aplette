/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "apl.h"
#include "utility.h"
#include "memory.h"
#include "fdat.h"
#include "data.h"
#include "main.h"

static char *gettoken(int ffile, char* buffer);
static void readFunction(int fd, SymTabEntry *newFunction);

void readErrorOnFailure(int fd, void* buf, size_t count) {
    int result = read(fd, buf, count);
    if (result < 0) {
        error(ERR, "attempt to read file failed");
    }
}

void writeErrorOnFailure(int fd, void* buf, size_t count) {
    int result = write(fd, buf, count);
    if (result < 0) {
        error(ERR, "attempt to write file failed");
    }
}

void wsload(int ffile)
{
    char buffer[64], *gettoken(), c;
    int use, size, rank, i, dim[MRANK];
    SymTabEntry* n;
    struct item* p;

    gettoken(ffile, buffer);
    if (!equal(buffer, "apl\\11"))
        error(ERR, "bad ws file magic number");
    gettoken(ffile, buffer);
    gettoken(ffile, buffer);
    tolerance = atof(buffer);
    gettoken(ffile, buffer);
    gettoken(ffile, buffer);
    iorigin = atoi(buffer);
    gettoken(ffile, buffer);
    gettoken(ffile, buffer);
    pagewidth = atoi(buffer);
    gettoken(ffile, buffer);
    gettoken(ffile, buffer);
    PrintP = atoi(buffer);

    while (1) {
        if (0 == gettoken(ffile, buffer))
            break;
        if (equal(buffer, "DA"))
            use = DA;
        if (equal(buffer, "CH"))
            use = CH;
        if (equal(buffer, "NF"))
            use = NF;
        if (equal(buffer, "MF"))
            use = MF;
        if (equal(buffer, "DF"))
            use = DF;

        gettoken(ffile, buffer);

        symtabIterateInit();
        while (n = symtabIterate()) {
            if (equal(buffer, n->namep)) {
                erase(n);
                goto hokay;
            }
        }
        n = symtabInsert(buffer);

    hokay:
        n->entryUse = use;
        if (n->entryUse == CH)
            n->entryUse = DA;
        n->entryType = LV;

        switch (use) {

        default:
            close(ffile);
            error(ERR, "bad ws file format");

        case DA:
        case CH:
            rank = atoi(gettoken(ffile, buffer));
            size = 1;
            for (i = 0; i < rank; i++) {
                dim[i] = atoi(gettoken(ffile, buffer));
                size *= dim[i];
            }
            p = newdat(use, rank, size);
            for (i = 0; i < rank; i++)
                p->dim[i] = dim[i];

            if (use == CH) {
                readErrorOnFailure(ffile, (char*) p->datap, size);
            }
            else {
                readErrorOnFailure(ffile, (data*)p->datap, size * sizeof(data));
            }

            n->itemp = p;
            break;

        case NF:
        case MF:
        case DF:
            readFunction(ffile, n);
            break;
        }
    }

    fdat(ffile);
    close(ffile);
}

static char *gettoken(int ffile, char* buffer) {
    int i;
    char c;

    i = 0;
    while (1) {
        if (read(ffile, &c, 1) != 1)
            return 0;
        if (isspace((int)c))
            continue;
        break;
    }
    buffer[i++] = c;
    while (1) {
        if (read(ffile, &c, 1) != 1)
            break;
        if (isspace(c))
            break;
        buffer[i++] = c;
    }
    buffer[i] = 0;
    return buffer;
}

// read a function into the workspace.
//
// The legacy format for workspaces is to have
// a line "MF functionName" (resp. "DF" or "NF", indicating arity of the function).
// then, a string of non-zero characters containing the source code for the
// function, with new-line characters separating individual lines, then
// a byte containing 0 as a flag that the function definition is complete.
//
// I'd like to change the above format to "MF functionName lineCount", followed
// by lineCount new-line terminated function source code lines.  And, dispense
// with the funny zero character at the end of the function.
// But, on the chance that there are some workspaces people have out there,
// I'll stick to the legacy workspace format for now.  - Greg J.
//
// given that we don't know how many lines we'll find when we start reading in
// the function, and that alloc.c does not have a realloc operation, we do things
// in a roundabout way:  malloc() and free our own local character array and read
// the function text into that array.  use realloc() along the way as necessary.
// then, count the number of source code lines, allocate the real array of
// line pointers based on that size, and copy from there.

static void readFunction(int fd, SymTabEntry *newFunction) {
    char *fnText;
    int fnTextLen;
    int fnTextUsed;

    fnText = (char *) malloc(32);
    fnTextLen = 32;
    fnTextUsed = 0;

    while (1) {
        char ch;
        int result;
        result = read(fd, &ch, 1);
        if (result != 1) {
            close(fd);
            error(ERR, "wsload unexpected eof");
        }
        if (ch == 0) break;

        if (fnTextUsed == fnTextLen) {
            fnTextLen *= 2;
            fnText = (char *) realloc(fnText, fnTextLen);
        }

        fnText[fnTextUsed++] = ch;
    }
    int lineCount = 0;
    int i;
    for (i = 0; fnText[i] != '\0'; ++i) {
        if (fnText[i] == '\n') {
            ++lineCount;
        }
    }
 
    int sourceCodeLen = 0;
    char lineBuf[LINEMAX];
    char *iline;
    int line;
    unsigned char ch;

    newFunction->itemp = 0;
    newFunction->label = 0;

    newFunction->sourceCodeCount = lineCount;

    newFunction->functionSourceCode = (char **) alloc(SPTR * lineCount);
    char *fnTextPtr = fnText;

    for (line = 0; line < lineCount; ++line) {
        int i;
        int lineLen = 0;

        while (1) {
            char ch = *fnTextPtr++;
            lineBuf[lineLen++] = ch;
            if (ch == (unsigned char) '\n') {
                lineBuf[lineLen] = '\0';
                break;
            }
        }

        if (ascii_characters) {
            iline = to_ascii_input(lineBuf);

        } else {
            iline = lineBuf;
        }

        newFunction->functionSourceCode[line] = (char *) alloc(strlen(iline) + 1);
        strcpy(newFunction->functionSourceCode[line], iline);

        if (ascii_characters) {
            aplfree((int *) iline);
        }
    }

    free(fnText);
}
