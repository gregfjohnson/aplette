/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <inttypes.h>
#include "apl.h"

char* ty[] = {
    0, "DA", "CH", "LV", "QD", "QQ", "IN", "EL", "NF", "MF", "DF", "QC", "QV", "NIL", "QX", "LB",
};

void stack_dump()
{
    struct item** p;
    int i, n;
    printf("---- stack top ----\n");
    /*
   printf("Stack limits are %x and %x \n", stack, stack + STKS - 1 );
 */
    for (p = sp - 1, n = -1; p >= stack; p--, n--) {
        printf("sp[%d]=%XH\n", n, p);
        continue; // pointer size != sizeof(int) bugs break the code below.
        // remove this continue when it is fixed.

        if (n == 0) {
            printf("\n");
        }
        else {
            printf("which is: type = ");
            if ((i = (*p)->type) >= 0 && i <= LBL && ty[i])
                printf("%s", ty[i]);
            else
                printf("%d", (*p)->type);
            switch (i) {
            default:
                putchar('\n');
                break;
            case LV:
                printf(",  n = %s\n", ((SymTabEntry*)*p)->namep);
                break;

            case CH:
                if ((*p)->size == 0) {
                    printf(",  rank = %d\n", (*p)->rank);
                    break;
                }
                if ((*p)->rank == 1) {
                    printf(",  \"");
                    for (i = 0; i < (*p)->size; i++)
                        putchar(((struct chrstrct*)(*p)->datap)->c[i]);
                    printf("\"\n");
                }
                else {
                    printf(",  rank = %d\n", (*p)->rank);
                }
                break;

            case DA:
            case LBL:
                if ((*p)->size == 0) {
                    printf(",  rank = %d\n", (*p)->rank);
                    break;
                }
                if ((*p)->rank == 0) {
                    printf(",  v = %f\n", (*p)->datap[0]);
                    break;
                }
                else {
                    printf(",  rank = %d\n", (*p)->rank);
                    break;
                }
            }
        }
    }
    printf("---- stack end ----\n");
}
