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
        thisContext->sp = 0;

        gsip = thisContext;
        do {
            gsip->text = get_QuadInput(S_QUAD_ASCII ":      ");

            if (gsip->text == NULL)
                error(ERR, "user input was null");

            compile_new(1);
        } while (gsip->pcode == 0); /* do it at least once */

        gsip->ptr = gsip->pcode;

        execute();

        p = *--sp;
        gsip = thisContext->prev; /* restore previous context */

        aplfree((int*)thisContext->text);
        aplfree((int*)thisContext->pcode);
        aplfree((int*)thisContext);

        return (p);

    } else {
        pop();
        ex_print();
        return (0);
    };
}
