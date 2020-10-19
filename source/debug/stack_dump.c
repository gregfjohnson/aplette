/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include <inttypes.h>
#include "apl.h"

static char* ty[] = {
    "XX", "DA", "CH", "LV", "QD", "QQ", "IN", "EL",
    "NF", "MF", "DF", "QC", "QV", "NIL", "QX", "LB",
    "PT" };

static char *bad_ItemType = "XX";

char *ItemType_str(ItemType t) {
    if (t >= 0 && t < NTYPES) {
        return ty[t];
    } else {
        return bad_ItemType;
    }
}

void stack_dump()
{
    struct item** p;
    int i, eu, n;
    printf("---- expr_stack top ----\n");

    // printf("Stack limits are %x and %x \n", expr_stack, expr_stack + STKS - 1 );

    for (p = expr_stack_ptr - 1, n = -1; p >= expr_stack; p--, n--) {
        printf("expr_stack_ptr[%d]=%p\n", n, (void *) p);

        if (n == 0) {
            printf("\n");

        } else {
            if (*p == 0) {
                printf("(null pointer)\n");
                continue;
            }

            printf("    which is: type = ");

            if ((i = (*p)->itemType) >= 0 && i < NTYPES && ty[i]) {
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
                if ((eu = sep->entryUse) >= 0 && eu < NTYPES && ty[eu]) {
                    printf("%s", ty[eu]);
                } else {
                    printf("%d", sep->entryUse);
                }

                printf(", itemType ");
                if ((eu = sep->itemType) >= 0 && eu < NTYPES && ty[eu]) {
                    printf("%s", ty[eu]);
                } else {
                    printf("%d", sep->itemType);
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
    printf("---- expr_stack end ----\n");
}
