/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "data.h"
#include "utility.h"
#include "opt_codes.h"
#include "userfunc.h"
#include "debug.h"
#include "execute.h"

void execute() {
    int opcode, i;
    data* dp;
    item_t *p, *p1;
    data (*data_fn)();
    extern char* opname[];

    state_indicator_ptr->ptr = state_indicator_ptr->pcode;

    if (code_trace) {
        code_dump(state_indicator_ptr->ptr, 0);
    }

    while (1) {
        if (stack_trace) {
            printf("execute loop:\n");
            stack_dump();
        }

        opcode = *state_indicator_ptr->ptr++;
        opcode &= 0377;
        lastop = opcode;
        if (opcode > OPT_MAX) {
            if (code_trace)
                printf(" opcode is %d \n", opcode);
            error(ERR_botch, "execute - unknown operand code");
        }
        if (code_trace && opcode >= 0)
            printf("   exec %s (0x%02x)\n", opname[opcode], opcode);

        switch (opcode) {

        default:
            error(ERR_botch, "execute - unknown operand");

        case END:
            goto epilog;

        case EOL:
            pop();
            break;

        case COMNT:
            *expr_stack_ptr++ = newdat(DA, 1, 0);
            break;

        case ADD:
        case SUB:
        case MUL:
        case DIV:
        case MOD:
        case MIN:
        case MAX:
        case PWR:
        case LOG:
        case CIR:
        case COMB:
        case AND:
        case OR:
        case NAND:
        case NOR:
            data_fn = (data (*)()) exop[opcode];
            p = fetch2();
            p1 = expr_stack_ptr[-2];
            ex_dscal(0, data_fn, p, p1);
            break;

        case LT:
        case LE:
        case GE:
        case GT:
            data_fn = (data (*)()) exop[opcode];
            p = fetch2();
            p1 = expr_stack_ptr[-2];
            ex_dscal(1, data_fn, p, p1);
            break;

        case EQ: /* 9.8.1999/tyl  */
        case NE:
            // for these two operators only, allow arguments
            // to have different types.
            data_fn = (data (*)()) exop[opcode];
            p = fetch2();
            p1 = expr_stack_ptr[-2];
            ex_dscal(2 /* allow different types */, data_fn, p, p1);
            break;

        case PLUS:
        case MINUS:
        case SGN:
        case RECIP:
        case ABS:
        case FLOOR:
        case CEIL:
        case EXP:
        case LOGE:
        case PI:
        case RAND:
        case FAC:
        case NOT:
            data_fn = (data (*)()) exop[opcode];
            p = fetch1();

            if (p->itemType != DA)
                error(ERR_domain, "type not supported by function");

            dp = p->datap;
            for (i = 0; i < p->size; i++) {
                *dp = (*data_fn)(*dp);
                dp++;
            }

            break;

        case MEPS: /*   execute         */
        case MENC: /*   monadic encode  */
        case DRHO:
        case DIOT:
        case EPS:
        case REP:
        case BASE:
        case DEAL:
        case DTRN:
        case CAT:
        case CATK:
        case TAKE:
        case DROP:
        case DDOM:
        case MDOM:
        case GDU:
        case GDUK:
        case GDD:
        case GDDK:
        case COM:
        case COM0:
        case COMK:
        case EXD:
        case EXD0:
        case EXDK:
        case ROT:
        case ROT0:
        case ROTK:
        case MRHO:
        case MTRN:
        case RAV:
        case RAVK:
        case RED:
        case RED0:
        case REDK:
        case SCAN:
        case SCANK:
        case SCAN0:
        case REV:
        case REV0:
        case REVK:
        case ASGN:
        case INDEX:
        case ELID:
        case IPROD:
        case OPROD:
        case IMMED:
        case HPRINT:
        case PRINT:
        case MIOT:
        case MIBM:
        case DIBM:
        case BRAN0:
        case BRAN:
        case FUN:
        case ARG1:
        case ARG2:
        case AUTO:
        case REST:
        case QRUN:
        case QEXEC:
        case FDEF:
        case QFORK:
        case QEXIT:
        case QWAIT:
        case QREAD:
        case QWRITE:
        case QUNLNK:
        case QRD:
        case QDUP:
        case QAP:
        case QKILL:
        case QSEEK:
        case QOPEN:
        case QCREAT:
        case QCLOSE:
        case QCHDIR:
        case QPIPE:
        case QCRP:
        case MFMT:
        case DFMT:
        case QNC:
        case NILRET:
        case LABEL:
        case SICLR:
        case SICLR0:
        case QSIGNL:
        case QFLOAT:
        case QNL:
        case QEX:
            (*exop[opcode])();
            break;

        case RVAL: { /* de-referenced LVAL */
            SymTabEntry *entry;
            state_indicator_ptr->ptr += copy(PTR, (char*)state_indicator_ptr->ptr, (char*)&entry, 1);

            entry = symtabFind(entry->namep);

            if (entry->entryUse != DA) {
                ex_nilret(); /* no fn rslt */

            } else {
                *expr_stack_ptr = fetch(entry);
                expr_stack_ptr++;
            }
            break;
        }

        case NAME:
            state_indicator_ptr->ptr += copy(PTR, (char*)state_indicator_ptr->ptr, (char*)expr_stack_ptr, 1);
            expr_stack_ptr++;
            break;

        case QUOT:
            /* prior to V0.14, strings were prefixed with their
	         * length which was limitted to 128 due to signed 
	         * int limit of 8bit character.
	         * Now strings are null terminated.
	         * the legacy of the string length prefix remains
	         * and should be removed from apl.y
	         */
            state_indicator_ptr->ptr++; /* throw away vcount */
            opcode = strlen(state_indicator_ptr->ptr);
            p = newdat(CH, opcode == 1 ? 0 : 1, opcode);
            state_indicator_ptr->ptr += copy(CH, (char*)state_indicator_ptr->ptr, (char*)p->datap, opcode);
            state_indicator_ptr->ptr++; /* jump past the null termination */
            *expr_stack_ptr++ = p;
            break;

        case CONST:

            opcode = *state_indicator_ptr->ptr++;
            p = newdat(DA, opcode == 1 ? 0 : 1, opcode);
            state_indicator_ptr->ptr += copy(DA, (char*)state_indicator_ptr->ptr, (char*)p->datap, opcode);
            *expr_stack_ptr++ = p;
            break;

        case QUAD:
        case QQUAD:
        case QLX:
        case QAV:
        case QTS:
        case QPP:
        case QPW:
        case QCT:
        case QIO:
        case QAI:
        case QARGV:
            p = newdat(QV, 0, 0);
            p->index = opcode;
            *expr_stack_ptr++ = p;
            break;
        }
    }

    epilog:

    if (stack_trace) {
        printf("end of execute:\n");
        stack_dump();
    }
}
