/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "utility.h"

void ex_float()
{

    /* Convert characters into either double-precision (apl)
    * or single-precision (apl2) format.  (Involves only
    * changing the data type and size declarations.
    */

    item_t* p;

    p = fetch1(); /* Get variable descriptor */

    if (p->itemType != CH)
        error(ERR_domain, "");                   /* Must be characters */

    if (p->rank == 0                             /* Scalar */
        || p->dim[(p->rank) - 1] % sizeof datum) /* Bad size */
        error(ERR_length, "");

    p->dim[p->rank - 1] /= sizeof datum; /* Reduce dimensions */
    p->size /= sizeof datum;             /* Reduce size */
    p->itemType = DA;                    /* Change data type */
}
