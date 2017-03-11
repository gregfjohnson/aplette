/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <stdio.h>
#include <unistd.h>

#include "apl.h"
#include "utility.h"
#include "opt_codes.h"
#include "memory.h"
#include "parser.h"
#include "userfunc.h"
#include "debug.h"
#include "data.h"

static char *strdupNoEoln(char *in);
static void reverse(char* s);
static char* catcode();

/*
 * funcomp - compile functions
 * during run time, a user defined function is invoked and
 * compiled before being executed.
 *
 * It uses a mix of buffered and nonbuf IO.
 *
 */

#define LABEL_PROLOG_LEN (1 + SPTR + 1 + 1 + SDAT + 1 + SPTR + 1 + 1)
#define LABEL_EPILOG_LEN (1 + SPTR + 1)
char *labcpp, *labcpe;

void funcomp(SymTabEntry* np) {
    int linesRead = 0;
    char labelProlog[MAXLAB * LABEL_PROLOG_LEN], labe[MAXLAB * LABEL_EPILOG_LEN];
    char *a, *c;
    int len1, len2;
    int i, err, err_code;
    char *iline, *status, *phase, *err_msg;
    Context *original_gsip, *functionLine, *Prologue, *Epilogue;
    Context **functionLines;
    int dbLineNum = 0;

    /* as gsip is used during compilation, we have to save the original
    * and restore it upon exit
    */
    original_gsip = gsip;
    err_code = 0;
    err_msg = "";

    dbLineNum = 0;
    err = 0;
    lineNumber = 0;

    /* Phase 1 creates the first of a linked list of compiled
   * function lines.  This first line will contain the prologue
   */
    if (code_trace) {
        fprintf(stderr, "Phase 1 \n");
    }
    phase = "Phase 1";
    Prologue = (Context*)alloc(sizeof(Context));
    Prologue->Mode = deffun;
    Prologue->suspended = 0;
    Prologue->prev = 0;
    Prologue->text = NULL;
    Prologue->pcode = NULL;
    Prologue->sp = 0;

    /* get the first line */
    if (dbLineNum < np->sourceCodeCount) {
        status = iline = np->functionSourceCode[dbLineNum++];
    } else {
        status = NULL;
    }

    if (0 == strlen(iline) || status == NULL) {
        err_code = ERR_implicit;
        err_msg = "empty header line";
        goto out;
    }
    else {
        ++linesRead;
    }

    Prologue->text = strdupNoEoln(iline);
    gsip = Prologue;
    labgen = 0;

    compile_new(CompileFunctionProlog);

    if (gsip->pcode == 0) {
        err_code = ERR_implicit;
        err_msg = "invalid header line";
        goto out;
    }

    /* Phase 2 compiles the body of the function */
    if (code_trace) {
        fprintf(stderr, "Phase 2 \n");
    }
    phase = "Phase 2";
    labcpp = labelProlog;
    labcpe = labe;
    labgen = 1;

    while (1) {
        if (dbLineNum < np->sourceCodeCount) {
            status = iline = np->functionSourceCode[dbLineNum++];
        } else {
            status = NULL;
        }

        if (0 == strlen(iline) || status == NULL) {
            break;
        }
        else {
            ++linesRead;
        }

        /* create a new Context */
        functionLine = (Context*)alloc(sizeof(Context));
        functionLine->Mode = deffun;
        functionLine->suspended = 0;
        functionLine->prev = gsip; /* link to previous */
        functionLine->pcode = NULL;
        functionLine->sp = 0;
        functionLine->text = strdupNoEoln(iline);

        lineNumber++;
        gsip = functionLine;
        compile_new(CompileFunctionBody);

        if (MAXLAB <= (labcpe - labe) / 5 + 1) {
            err_code = ERR_botch;
            err_msg = "too many labels, edit MAXLAB in apl.h and recompile";
            goto out;
        }

        if (gsip->pcode == 0) {
            err++;
        }
    }

    if (err) {
        err_code = ERR_implicit;
        err_msg = "compilation errors";
        goto out;
    }

    /* At the end of this Phase, lineNumber = Maximum_No_of_lines
     * but we want to include the Prologue (line 0) and 
     * Epilogue (so add one to lineNumber)
     */
    lineNumber++;

    if (code_trace) {
        fprintf(stderr, "At end of Phase 2...\n");
        for (i = lineNumber; i > 1; i--) {
            fprintf(stderr, "[%d] ", i - 1);
            code_dump(functionLine->pcode, 0);
            functionLine = functionLine->prev;
        }
        fprintf(stderr, "[p] ");
        code_dump(Prologue->pcode, 0);
        fprintf(stderr, "[0] %d\n", lineNumber);
    }

    /* Phase 3 - dealing with labels */
    phase = "Phase 3a";

    /* generate the Epilogue */

    // reset the file read pointer to the beginning of this function..
    dbLineNum = 0;

    if (dbLineNum < np->sourceCodeCount) {
        status = iline = np->functionSourceCode[dbLineNum++];
    } else {
        status = NULL;
    }

    if (0 == strlen(iline)) {
        err++;
        err_code = ERR_implicit;
        goto out;
    }

    Epilogue = (Context*)alloc(sizeof(Context));
    Epilogue->Mode = deffun;
    Epilogue->suspended = 0;
    Epilogue->prev = gsip;
    Epilogue->text = strdupNoEoln(iline);
    Epilogue->pcode = NULL;
    Epilogue->sp = 0;
    labgen = 0;
    gsip = Epilogue;

    compile_new(CompileFunctionEpilog);

    if (gsip->pcode == 0) {
        err_code = ERR_implicit;
        err_msg = "invalid header line";
        goto out;
    }

    /* only conduct phase 3b/c if labels were generated */
    if (labcpp != labelProlog) {
        phase = "Phase 3b";
        /* append the label-epilogue to the Epilogue */
        reverse(labe);
        c = Epilogue->pcode;
        Epilogue->pcode = catcode(labe, c);
        aplfree((int*)c);

        phase = "Phase 3c";
        /* At this point, we have:
         * fn-prologue (pcodeLines[1]):      <AUTOs and ARGs>, ELID, END
         * local array labelProlog:          <AUTOs and LABELs>, END
         * 
         * and we want to produce:
         * fn-prologue (pcodeLines[1]):   <AUTOs and ARGs>,<AUTOs and LABELs>,  ELID, END.
         */
        len1 = csize(Prologue->pcode) - 1;
        len2 = csize(labelProlog) - 1;

        /* Move the ELID from the end of the fn-prologue,
       * to the end of the label-prologue.
       */
        if (Prologue->pcode[len1 - 1] == ELID) {
            Prologue->pcode[len1 - 1] = END;
            labelProlog[len2] = ELID;
            labelProlog[len2 + 1] = END;
        }
        else {
            err_code = ERR_botch;
            err_msg = "elid";
            goto out;
        }

        /* Append the label-prologue to the Prologue */
        a = Prologue->pcode;
        Prologue->pcode = catcode(a, labelProlog);
        aplfree((int*) a);
    }

    if (code_trace) {
        code_dump(Prologue->pcode, 1); /* show the prologue */
        code_dump(Epilogue->pcode, 1); /* show the epilogue */
    }

    /* Phase 4 goes through the compiled lines
   * storing pointers to each pcode in pcodeLines[]
   */
    if (code_trace) {
        fprintf(stderr, "Phase 4 \n");
    }
    phase = "Phase 4";
    functionLines = (Context **)alloc((linesRead + 1) * SPTR);
    functionLine = Epilogue;
    for (i = linesRead; i >= 0; --i) {
        functionLines[i] = functionLine;
        functionLine = functionLine->prev;
    }

    if (code_trace) {
        fprintf(stderr, "At end of Phase 4...\n");
        fprintf(stderr, "[p] ");
        code_dump(functionLines[0]->pcode, 0);
        for (i = 1; i < linesRead; i++) {
            fprintf(stderr, "[%d] ", i);
            code_dump(functionLines[i]->pcode, 0);
        }
        fprintf(stderr, "[e] ");
        code_dump(functionLines[linesRead]->pcode, 0);
    }

    /* put the result into effect */

    // functionLineCount is one larger than the APL function line number
    // of the last line of this function.  i.e., if gsip->funlc >= functionLineCount
    // or gsip->funlc <= 0, the function is done and should exit.
    // if the function body goes from [1] to [N], we will have read N+1 lines
    // counting the function header.  So, N+1 is the number we are looking for.

    np->functionLineCount = linesRead;
    np->functionLines = functionLines;
    np->functionLineLength = linesRead + 1;

    err = 0;

out:
    if (code_trace) {
        fprintf(stderr, "Phase out \n");
    }

    gsip = original_gsip;
    if (err_code) {
        if (np->namep)
            printf("%s in function %s\n", phase, np->namep);
        error(err_code, err_msg);
    }
}

static void reverse(char* s) {
    char *p, *q, c;
    int j;

    p = q = s;
    while (*p != END)
        p++;
    p -= 1 + sizeof(char*);
    while (q < p) {
        for (j = 0; j < 1 + sizeof(char*); j++) {
            c = p[j];
            p[j] = q[j];
            q[j] = c;
        }
        q += j;
        p -= j;
    }
}

static char *catcode(char *s1, char *s2) {
    int i, j;
    char *p, *q;

    i = csize(s1) - 1;
    j = csize(s2);
    p = q = (char *) alloc(i + j);
    p += copy(CH, s1, p, i);
    copy(CH, s2, p, j);
    return (q);
}

static char *strdupNoEoln(char *in) {
    char *result;
    int len = strlen(in);
    while (len > 0 && in[len-1] == '\n') --len;
    result = strndup(in, len + 1);
    return result;
}
