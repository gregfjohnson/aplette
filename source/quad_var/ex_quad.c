/* openAPL, Copyright (C) Branko Bratkovic 1998
 * This file is free software and is covered by the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 *
 * For more details see the GNU General Public License (GPL) in
 * the docs directory.
 */
#include <stdio.h>
#include <unistd.h>

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"
#include "memory.h"
#include "parser.h"
#include "execute.h"
#include "print.h"
#include "getinput.h"

struct item* ex_quad(io) int io; /* 0 = source, 1 = sink */
{
    struct item* p;
    Context* thisContext;

    if (io == 0) {
        thisContext = (Context*)alloc(sizeof(Context));
        thisContext->prev = gsip; /* setup new context */
        thisContext->Mode = deffun;
        //thisContext->np = np;
        thisContext->sp = 0;
        //thisContext->ptr = thisContext->pcode;
        //thisContext->funlc = 0;
        //thisContext->suspended = 0;

        gsip = thisContext;
        do {
            gsip->text = getinput(S_QUAD_ASCII ":      ");
            if (!isatty(0))
                printf("%s", gsip->text);
            if (gsip->text == NULL)
                error(ERR, "user input was null");
            compile_new(1);
        } while (gsip->pcode == 0); /* do it at least once */
        //i = pcp;
        gsip->ptr = gsip->pcode;
        execute();
        //pcp = i;
        p = *--sp;
        gsip = thisContext->prev; /* restore previous context */
        aplfree((int*)thisContext->text);
        aplfree((int*)thisContext->pcode);
        aplfree((int*)thisContext);
        //pcp = context->oldpcp;
        return (p);
    }
    else {
        pop();
        ex_print();
        return (0);
    };
}
