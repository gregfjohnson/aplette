/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "memory.h"
#include "parser.h"
#include "execute.h"
#include "userfunc.h"

/* the primitive function "execute" (uptack jot) */
void ex_execute()
{
    item_t* p;
    int i, dim0, dim1;
    char* b;
    Context* thisContext;

    p = fetch1();
    if (p->rank > 2)
        error(ERR_rank, "");
    if (p->itemType != CH)
        error(ERR_domain, "not a literal value");
    /*get out if nothing to do, apr 2-23-77 */
    if (p->size == 0)
        return;

    b = (char*)p->datap;
    dim0 = p->rank < 2 ? 1 : p->dim[0];
    dim1 = p->rank < 2 ? p->size : p->dim[1];

    thisContext = (Context*)alloc(sizeof(Context));
    thisContext->prev = state_indicator_ptr; /* setup new context */
    thisContext->text = (char*)alloc(dim1 + 1);
    thisContext->Mode = exec;
    thisContext->expr_stack_ptr = expr_stack_ptr;
    thisContext->suspended = 0;
    state_indicator_ptr = thisContext;

    for (i = 0; i < dim0; i++) {
        copy(CH, b, state_indicator_ptr->text, dim1);
        state_indicator_ptr->text[dim1] = '\n';
        compile_new(CompileQuadInput);

        if (state_indicator_ptr->pcode != 0) {
            state_indicator_ptr->ptr = state_indicator_ptr->pcode;
            state_indicator_ptr->expr_stack_ptr = expr_stack_ptr;
            execute();
            aplfree((int*)state_indicator_ptr->pcode);
            if (state_indicator_ptr->expr_stack_ptr == expr_stack_ptr)
                ex_nilret();
        }
        else {
            state_indicator_ptr = thisContext->prev; /* restore previous context */
            aplfree((int*)thisContext->text);
            aplfree((int*)thisContext);

            error(ERR_implicit, "error during execute");
        }
        b += dim1;
        if (i < dim0 - 1)
            pop();
    }
    aplfree((int*)thisContext->text);
    state_indicator_ptr = thisContext->prev; /* restore previous context */
    aplfree((int*)thisContext);
    p = *--expr_stack_ptr;
    pop();
    *expr_stack_ptr++ = p;
}
