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
    int i, eu, n;
    printf("---- stack top ----\n");

    // printf("Stack limits are %x and %x \n", stack, stack + STKS - 1 );

    for (p = sp - 1, n = -1; p >= stack; p--, n--) {
        printf("sp[%d]=%p\n", n, (void *) p);

        if (n == 0) {
            printf("\n");

        } else {
            if (*p == 0) {
                printf("(null pointer)\n");
                continue;
            }

            printf("    which is: type = ");

            if ((i = (*p)->itemType) >= 0 && i <= LBL && ty[i]) {
                printf("%s", ty[i]);
            } else {
                printf("%d", (*p)->itemType);
            }

            switch (i) {
            default:
                putchar('\n');
                break;

            case LV: {
                SymTabEntry* sep = (SymTabEntry*)*p;
                printf(",  n = %s", sep->namep);

                printf(", entryUse ");
                if ((eu = sep->entryUse) >= 0 && eu <= LBL && ty[eu]) {
                    printf("%s", ty[eu]);
                } else {
                    printf("%d", sep->entryUse);
                }

                printf(", entryType ");
                if ((eu = sep->entryType) >= 0 && eu <= LBL && ty[eu]) {
                    printf("%s", ty[eu]);
                } else {
                    printf("%d", sep->entryType);
                }

                printf("\n");
                break;
            }

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
