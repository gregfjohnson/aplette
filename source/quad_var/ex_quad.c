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

item_t* ex_quad(io) int io; /* 0 = source, 1 = sink */
{
    item_t* p;
    Context* thisContext;

    if (io == 0) {
        thisContext = (Context*)alloc(sizeof(Context));
        thisContext->prev = state_indicator_ptr; /* setup new context */
        thisContext->Mode = deffun;
        thisContext->expr_stack_ptr = 0;

        state_indicator_ptr = thisContext;
        do {
            state_indicator_ptr->text = get_QuadInput(S_QUAD_ASCII ":      ");

            if (state_indicator_ptr->text == NULL)
                error(ERR, "user input was null");

            compile_new(CompileQuadInput);
        } while (state_indicator_ptr->pcode == 0); /* do it at least once */

        state_indicator_ptr->ptr = state_indicator_ptr->pcode;

        execute();

        p = *--expr_stack_ptr;
        state_indicator_ptr = thisContext->prev; /* restore previous context */

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
