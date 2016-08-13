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
        case DF: {
            int sourceCodeLen = 0;
            char lineBuf[LINEMAX];
            char *iline;
            int line;
            unsigned char ch;
            int lineCount = atoi(gettoken(ffile, buffer));

            // while (1 == read(ffile, &ch, 1) && ch != (unsigned char) '\n');

            n->itemp = 0;
            n->label = 0;

            n->sourceCodeCount = lineCount;

            n->functionSourceCode = (char **) alloc(SPTR * lineCount);

            for (line = 0; line < lineCount; ++line) {
                int i;
                int lineLen = 0;

                while (1) {
                    int result;
                    result = read(ffile, &ch, 1);
                    if (result != 1) {
                        close(ffile);
                        error(ERR, "wsload unexpected eof");
                    }
                    lineBuf[lineLen++] = ch;
                    if (ch == (unsigned char) '\n') break;
                }
                lineBuf[lineLen] = '\0';

                if (ascii_characters) {
                    iline = to_ascii_input(lineBuf);

                } else {
                    iline = lineBuf;
                }

                n->functionSourceCode[line] = (char *) alloc(strlen(iline) + 1);
                strcpy(n->functionSourceCode[line], iline);

                if (ascii_characters) {
                    aplfree((int *) iline);
                }
            }

            break;
        }
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
