/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"

/*
 * scalar -- return true if arg is a scalar 
 */
int scalar(item_t* aip)
{
    return (aip->size == 1);
}
