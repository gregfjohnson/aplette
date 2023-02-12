/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"
#include "memory.h"

// allowed types:
item_t* newdat(ItemType type, int rank, int size) {
    item_t* p;
    void* q = NULL;

    /* Allocate a new data item.  I have searched the specifications
    * for C and as far as I can tell, it should be legal to
    * declare a zero-length array inside a structure.  However,
    * the VAX C compiler (which I think is a derivative of the
    * portable C compiler) does not allow this.  The Ritchie
    * V7 PDP-11 compiler does.  I have redeclared "dim" to
    * contain MRANK elements.  When the data is allocated,
    * space is only allocated for as many dimensions as there
    * actually are.  Thus, if there are 0 dimensions, no space
    * will be allocated for "dim".  This had better make the
    * VAX happy, since it has sure made me unhappy.
    *
    * --John Bruner
    */

    if (type != CH && type != DA && type != EL && type != NIL && type != QV) {
        error(ERR_botch, "newdat:  type is unknown");
    }

    if (rank > MRANK)
        error(ERR_rank, "maximum rank exceeded");

    /* create data storage for those types that required it */
    switch (type) {
    case DA:
        q = alloc(size * SDAT);
        break;

    case CH:
        q = alloc(size);
        break;

    default:
        break;
    }

    p = (item_t*)alloc(sizeof(*p));
    /* populate it */
    p->rank = rank;
    p->itemType = type;
    p->size = size;
    p->index = 0;
    if (rank == 1)
        p->dim[0] = size;
    p->datap = q;
    return (p);
}
