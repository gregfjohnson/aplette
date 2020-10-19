#include "apl.h"
#include "data.h"
#include "utility.h"

/* this routine deals with dyadic scalar functions
 * with different argument types.  only used for
 * functions "equal" and "not_equal".  In the former
 * case, return all 0's, in the latter case return
 * all 1's.
 * (provided shapes are compatible.)
 */

/* function added by tyl */
void ex_mdyad(data (*f)(), struct item* argptr0, struct item* argptr1) {
    int i;
    struct item *use_dims;
    struct item *result;

    if (argptr0->rank == 0 || argptr0->size == 1) {
        use_dims = argptr1;

    } else if (argptr1->rank == 0 || argptr1->size == 1) {
        use_dims = argptr0;

    } else {
        if (argptr0->rank != argptr1->rank)
            error(ERR_rank, "mixdyad - arrays do not match");

        for (i = 0; i < argptr0->rank; i++) {
            if (argptr0->dim[i] != argptr1->dim[i])
                error(ERR_length, "mixdyad - arrays do not match");
        }
        use_dims = argptr0;
    }

    result = newdat(DA, use_dims->rank, use_dims->size);

    for (i = 0; i < use_dims->rank; ++i)
        result->dim[i] = use_dims->dim[i];

    // test case to see if "f" implements "equal" or "not_equal".
    data value = (*f)((data) 0., (data) 1.);

    // fill the result array with the result.
    //
    for (int i = 0; i < use_dims->size; ++i)
        result->datap[i] = value;

    pop();
    pop();
    *expr_stack_ptr++ = result;
}
