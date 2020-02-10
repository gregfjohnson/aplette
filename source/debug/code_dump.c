/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "char.h"
#include "opt_codes.h"
#include "data.h"

/* WARNING, the following must agree with opt_codes.h and optcodes.c */

char* opname[] = {

    "eol",          /* 0 */
    "end",          /* 1 */
    "add",          /* 2 */
    "plus",         /* 3 */
    "sub",          /* 4 */
    "minus",        /* 5 */
    "mul",          /* 6 */
    "sgn",          /* 7 */
    "div",          /* 8 */
    "recip",        /* 9 */
    "mod",          /* 10 */
    "abs",          /* 11 */
    "min",          /* 12 */
    "floor",        /* 13 */
    "max",          /* 14 */
    "ceil",         /* 15 */
    "pwr",          /* 16 */
    "exp",          /* 17 */
    "log",          /* 18 */
    "loge",         /* 19 */
    "cir",          /* 20 */
    "pi",           /* 21 */
    "comb",         /* 22 */
    "fac",          /* 23 */
    "deal",         /* 24 */
    "rand",         /* 25 */
    "drho",         /* 26 */
    "mrho",         /* 27 */
    "diot",         /* 28 */
    "miot",         /* 29 */
    "rot0",         /* 30 */
    "rev0",         /* 31 */
    "dtrn",         /* 32 */
    "mtrn",         /* 33 */
    "dibm",         /* 34 */
    "mibm",         /* 35 */
    "gdu",          /* 36 */
    "gduk",         /* 37 */
    "gdd",          /* 38 */
    "gddk",         /* 39 */
    "exd",          /* 40 */
    "scan",         /* 41 */
    "exdk",         /* 42 */
    "scank",        /* 43 */
    "iprod",        /* 44 */
    "oprod",        /* 45 */
    "quad",         /* 46 */
    "qquad",        /* 47 */
    "br0",          /* 48 */
    "br",           /* 49 */
    "ddom",         /* 50 */
    "mdom",         /* 51 */
    "com",          /* 52 */
    "red",          /* 53 */
    "comk",         /* 54 */
    "redk",         /* 55 */
    "rot",          /* 56 */
    "rev",          /* 57 */
    "rotk",         /* 58 */
    "revk",         /* 59 */
    "cat",          /* 60 */
    "rav",          /* 61 */
    "catk",         /* 62 */
    "ravk",         /* 63 */
    "print",        /* 64 */
    "quot",         /* 65 */
    "elid",         /* 66 */
    "cquad",        /* 67 */
    "comnt",        /* 68 */
    "index",        /* 69 */
    "hprint",       /* 70 */
    "lt",           /* 71 */
    "le",           /* 72 */
    "gt",           /* 73 */
    "ge",           /* 74 */
    "eq",           /* 75 */
    "ne",           /* 76 */
    "and",          /* 77 */
    "or",           /* 78 */
    "nand",         /* 79 */
    "nor",          /* 80 */
    "not",          /* 81 */
    "eps",          /* 82 */
    "meps",         /* 83 */
    "rep",          /* 84 */
    "take",         /* 85 */
    "drop",         /* 86 */
    "exd0",         /* 87 */
    "asgn",         /* 88 */
    "immed",        /* 89 */
    "name",         /* 90 */
    "const",        /* 91 */
    "fun",          /* 92 */
    "arg1",         /* 93 */
    "arg2",         /* 94 */
    "auto",         /* 95 */
    "rest",         /* 96 */
    "com0",         /* 97 */
    "red0",         /* 98 */
    "exd0",         /* 99 */
    "scan0",        /*100 */
    "base",         /*101 */
    "format",       /*102 */
    "label",        /*103 */
    0,              /*104 */
    S_QUAD "lx",    /*105 */
    S_QUAD "av",    /*106 */
    S_QUAD "ts",    /*107 */
    S_QUAD "pp",    /*108 */
    S_QUAD "pw",    /*109 */
    S_QUAD "ct",    /*110 */
    S_QUAD "io",    /*111 */
    S_QUAD "run",   /*112 */
    S_QUAD "fork",  /*113 */
    S_QUAD "wait",  /*114 */
    S_QUAD "exec",  /*115 */
    S_QUAD "fx",    /*116 */
    S_QUAD "exit",  /*117 */
    S_QUAD "pipe",  /*118 */
    S_QUAD "chdir", /*119 */
    S_QUAD "open",  /*120 */
    S_QUAD "close", /*121 */
    S_QUAD "read",  /*122 */
    S_QUAD "write", /*123 */
    S_QUAD "creat", /*124 */
    S_QUAD "seek",  /*125 */
    S_QUAD "rm",    /*126 */
    S_QUAD "rd",    /*127 */
    S_QUAD "dup",   /*128 */
    S_QUAD "ap",    /*129 */
    S_QUAD "kill",  /*130 */
    S_QUAD "cr",    /*131 */
    "dfmt",         /*132 */
    "mfmt",         /*133 */
    S_QUAD "nc",    /*134 */
    "nilret",       /*135 */
    S_QUAD "lx",    /*136 */
    "ibr",          /*137 */
    "ibr0",         /*138 */
    "rval",         /*139 */
    S_QUAD "sig",   /*140 */
    S_QUAD "float", /*141 */
    S_QUAD "nl",    /*142 */
    S_QUAD "ex",    /*143 added 14.8.1999/tyl */
    S_QUAD "ai",    /*144 		-""-	*/
};

/* System Command op-codes */
char* sysops[] = {

    "err",     /* 0 */
    "clear",   /* 1 */
    "err",     /* 0 */
    "edit",    /* 3 */
    "erase",   /* 4 */
    "fns",     /* 5 */
    "err",     /* 0 */
    "read",    /* 7 */
    "err",     /* 0 */
    "vars",    /* 9 */
    "err",     /* 0 */
    "debug",   /* 11 */
    "off",     /* 12 */
    "load",    /* 13 */
    "save",    /* 14 */
    "copy",    /* 15 */
    "contin",  /* 16 */
    "lib",     /* 17 */
    "dropc",   /* 18 */
    "err",     /* 0 */
    "script",  /* 20 */
    "dell",    /* 21 */
    "trace",   /* 22 */
    "untarce", /* 23 */
    "write",   /* 24 */
    "siclear", /* 25 */
    "sicom",   /* 26 */
    "code",    /* 27 */
    "err",     /* 0 */
    "shell",   /* 29 */
    "list",    /* 30 */
    "prws",    /* 31 */
    "memory",  /* 32 */
};

void code_dump(char* cp, int flag)
{
    char *s, *t;
    int i;

    s = cp;
    if (flag)
        fprintf(stderr, "[ ");

    int index = 0;

loop:
    fprintf(stderr, "\n    <%d; %p> ", index++, (void *) s);

    if (column > 50) {
        if (flag)
            fprintf(stderr, " ]\n[ ");
        else
            fprintf(stderr, "\n");
    }

    i = *s++;
    i &= 0377;

    if (i >= 0 && i <= OPT_MAX && opname[i]) {
        t = opname[i];
        while (*t)
            fprintf(stderr, "%c", *t++);

    } else if (i != END) {
        fprintf(stderr, "%d ", i);
    }

    switch (i) {
        case EOL:
            if (*s != EOL)
                break;

        case END:
            if (flag)
                fprintf(stderr, " ]");
            fprintf(stderr, "\n");
            return;

        case QUOT:
            i = *s++; /* throw away vcount, see notes in execute() */
            i = strlen(s);
            fprintf(stderr, "-");
            fprintf(stderr, "%s ", s);
            //s += i;
            s += i + 1; /* jump past null termination */
            break;

        case CONST:
            i = *s++;
            s += i * SDAT;
            break;

        case NAME:
        case FUN:
        case ARG1:
        case ARG2:
        case AUTO:
        case REST:
        case RVAL: {
            SymTabEntry* entry;
            s += copy(PTR, (char*)s, (char*)&entry, 1);
            fprintf(stderr, "-%s <symtab %p>", entry->namep, (void *) entry);
            break;
        }

        case INDEX:
            s++;
            break;

        case IMMED:
            i = *s++;
            fprintf(stderr, "-");
            if (i > 0 && i <= 32 && sysops[i]) {
                t = sysops[i];
                while (*t)
                    fprintf(stderr, "%c", *t++);
            }
            break;
    }

    goto loop;
}
