/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "apl.h"
#include "utility.h"
#include "opt_codes.h"
#include "data.h"
#include "work_space.h"
#include "main.h"
#include "debug.h"
#include "userfunc.h"
#include "parser.h"
#include "listdir.h"
#include "ex_shell.h"
#include "ex_list.h"
#include "ex_prws.h"
#include "quad_var.h"

static int nextMultOfEight(int n);

void ex_syscom()
{
    int i, *ip, j;
    struct item* p;
    SymTabEntry* n;
    char fname[64]; /* Array for filename */
    char *cp, *vfname();
    int nameLen;

    i = *gsip->ptr++;
    switch (i) {

    default:
        error(ERR_implicit, "unrecognised system function");

    case SCRIPT:
        SECURITY_CHECK;
        if (protofile > 0)
            close(protofile);
        protofile = 0;
        cp = vfname(fname);
        if (equal(cp, "off"))
            return;
        if ((protofile = open(cp, 1)) > 0) {
            lseek(protofile, 0L, SEEK_END); /* append to existing file */
            printf("[appending]\n");
        }
        else {
            /*
          * create new file
          */
            protofile = opn(cp, 0644);
            printf("[new file]\n");
        }
        writeErrorOnFailure(protofile, "\t)script on\n", 12);
        return;

    case DEBUG:
        code_trace = !code_trace;
        stack_trace = !stack_trace;
        funtrace = !funtrace;
        return;

    case MEMORY:
        mem_dump();
        return;

    case DIGITS:
        if (exprOrNullFlag) {
            p = sp[-1];
            sp--;
            updatePrintP(p);
            outputPrintP();

        } else {
            outputPrintP();
        }
        return;

    case TRACE:
        funtrace = 1;
        return;

    case UNTRACE:
        funtrace = 0;
        return;

    case WRITE:
        funwrite(0);
        return;

    case DELL:
        funstdin();
        return;

    case EDIT:
        SECURITY_CHECK;
        funedit(0);
        return;

    case READ:
        funread(0);
        return;

    case ERASE:
        p = sp[-1];
        sp--;
        erase((SymTabEntry*) p);
        if (vars_trace)
            vars_dump();
        return;

    case CONTIN:
        i = opn("continue", 0644);
        wssave(i);
        printf(" continue");

    case FONT:
        font_map_print();
        return;

    case OFF:
        Exit(0);

    case VARS:
        symtabIterateInit();
        column = 0;
        while (n = symtabIterate()) {
            if (n->itemp && n->entryUse == DA) {
                if (column + strlen(n->namep) >= pagewidth) {
                    printf("\n\t");
                    column = 8;
                }

                printf("%s%n", n->namep, &nameLen);
                column += nameLen;

                putchar('\t');
                column = nextMultOfEight(column);
            }
        }
        putchar('\n');
        return;

    case FNS:
        symtabIterateInit();
        while (n = symtabIterate()) {
            if (n->entryUse == DF || n->entryUse == MF || n->entryUse == NF) {
                if (column + strlen(n->namep) >= pagewidth) {
                    printf("\n\t");
                    column = 8;
                }
                printf("%s%n", n->namep, &nameLen);
                column += nameLen;

                putchar('\t');
                column = nextMultOfEight(column);
            }
        }
        putchar('\n');
        column = 0;

        return;

    case CODE:
        n = (SymTabEntry*)sp[-1];
        sp--;
        switch (n->entryUse) {
        default:
            error(ERR_implicit, "function name not found");
        case NF:
        case MF:
        case DF:
            if (n->itemp == 0)
                funcomp(n);
        {
            fprintf(stderr, "[p] ");
            code_dump(n->functionLines[0]->pcode, 0);
            for (i = 1; i < n->functionLineCount; i++) {
                fprintf(stderr, "[%d] ", i);
                code_dump(n->functionLines[i]->pcode, 0);
            }
            fprintf(stderr, "[e] ");
            code_dump(n->functionLines[n->functionLineCount]->pcode, 0);
        }
        }
        return;

    case SICLEAR:
        while (gsip != &prime_context) {
            ex_ibr0();
        }
        longjmp(cold_restart, 0);

    case SICOM:
        tback(1);
        return;

    case CLEAR:
        clear();
        printf("clear ws\n");
        goto warp1; /* four lines down, or so... */

    case LOAD:
        j = opn(vfname(fname), O_RDONLY);
        clear();
        wsload(j);
        printf(" %s\n", fname);
        eval_qlx(); /* possible latent expr evaluation */
    warp1:
        /*
       * this garbage is necessary because clear()
       * does a brk(&end), and the normal return & cleanup
       * procedures are guaranteed to fail (miserably).
       *      --jjb 1/78
       */
        sp = stack;
        longjmp(cold_restart, 0);
    //longjmp(reset_env, 0);
    //longjmp(gsip->env, 0);

    case LIB:
        listdir();
        return;

    case COPY:
        if (gsip != &prime_context) {
            error(ERR_implicit, "si damage -- type ')sic'");
        }
        wsload(opn(vfname(fname), 0));
        printf(" copy %s\n", fname);
        return;

    case DROPC:
        SECURITY_CHECK;
        cp = vfname(fname);
        if (unlink(cp) == -1)
            printf("[can't remove %s]\n", cp);
        return;

    case SAVE:
        SECURITY_CHECK;
        j = opn(vfname(fname), 0644);
        wssave(j);
        printf(" saved %s\n", fname);
        return;

    case SHELL:
        SECURITY_CHECK;
        ex_shell();
        return;

    case LIST:
        ex_list();
        return;

    case PRWS:
        ex_prws();
        return;

    case LICENSE:
        printf("openAPL, Copyright (C) Branko Bratkovic 1998, 1999");
        printf("\n");
        printf("This program is free software; you can redistribute it");
        printf(" and/or modify\n");
        printf("it under the terms of the GNU General Public License");
        printf(" as published by\n");
        printf("the Free Software Foundation; either version 2 of");
        printf(" the License, or\n");
        printf("(at your option) any later version.\n");
        printf("\n");
        printf("This program is distributed in the hope that it will");
        printf(" be useful,\n");
        printf("but WITHOUT ANY WARRANTY; without even the implied");
        printf(" warranty of\n");
        printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.");
        printf(" See the\n");
        printf("GNU General Public License for more details.\n");
        printf("\n");
        printf("You should have received a copy of the GNU General");
        printf(" Public License\n");
        printf("along with this program; if not, write to the Free");
        printf(" Software\n");
        printf("Foundation, Inc., 59 Temple Place, Suite 330, Boston,");
        printf(" MA  02111-1307  USA\n");
        return;
    }
}

char* vfname(char* array) {
    SymTabEntry* n;
    char* p;

    n = (SymTabEntry*)sp[-1];
    sp--;
    if (n->entryType != LV)
        error(ERR_value, "not a local varaible");
    p = n->namep;
    while (*array++ = *p++)
        ;
    return (n->namep);
}

static int nextMultOfEight(int n) {
    return 8 * ((n+7) / 8);
}
