/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <math.h>
#include "apl.h"
#include "data.h"
#include "utility.h"
#include "memory.h"

static int lsq(data* dmn, data* dn1, data* dn2, data* dn3, data* dm, int* in,
    int n, int m, int lhs_cols,
    data* d1, data* d2);

static void solve(int m, int n, data* dmn, data* dn2, int* in, data* dm, data* dn1);

static void pmat(char *title, data *elts, int rows, int cols);
static void pmat_T(char *title, data *elts, int rows, int cols);
static void pint(char *title, int *elts, int rows);

void ex_ddom()
{
    struct item *p, *q;
    int row, col, m, rows, cols, lhs_cols, *in;
    data *d1, *dmn, *dn1, *dn2, *dn3, *dm;
    char* al;

    p = fetch2();
    q = sp[-2];

    if (p->itemType != DA || q->itemType != DA)
        error(ERR_domain, "domino - incorrect types");

    if ((p->rank != 1 && p->rank != 2) || q->rank != 2)
        error(ERR_rank, "domino - unexpected ranks");

    rows = q->dim[0];
    cols = q->dim[1];
    if (rows < cols || rows != p->dim[0])
        error(ERR_rank, "domino - mismatch");
    lhs_cols = 1;
    if (p->rank == 2)
        lhs_cols = p->dim[1];

    /*
    al:
        lhs[cols][rows];
        {
            int n;
            data work[3];
        } [cols];

        data rhs[rows];
    */
    // work areas for lsq()..
    #if 1
        al = (char*)alloc(cols * (SINT + SDAT * rows + SDAT * 3) + SDAT * rows);
        if (al == 0)
            error(ERR, "domino - unable to allocate memory");

        // data array of dimension rows x cols
        dmn = (data*)al;

        // data array of dimension cols
        dn1 = dmn + rows * cols;

        // data array of dimension cols
        dn2 = dn1 + cols;

        // data array of dimension cols
        dn3 = dn2 + cols;

        // data array of dimension rows
        dm = dn3 + cols;

        // int array of dimension cols
        in = (int*)(dm + rows);

    #else
        dmn = (data*) alloc(rows*cols * SDAT);
        dn1 = (data*) alloc(cols * SDAT);
        dn2 = (data*) alloc(cols * SDAT);
        dn3 = (data*) alloc(cols * SDAT);
        dm  = (data*) alloc(rows * SDAT);
        in  = (int*)  alloc(cols * SINT);
    #endif

    pmat("input rhs", q->datap, rows, cols);
    pmat("input lhs", p->datap, rows, 1);

    // copy the RHS matrix into the work area, transposing as we go..
    d1 = q->datap;
    for (col = 0; col < rows; col++) {
        for (row = 0; row < cols; row++)
            dmn[row * rows + col] = *d1++;
    }

    pmat_T("lsq dmn", dmn,rows,cols);
    int result = lsq(dmn, dn1, dn2, dn3, dm, in, rows, cols, lhs_cols, p->datap, q->datap);
    aplfree((int*)dmn);

    if (result)
        error(ERR, "domino - could not solve");

    sp--;
    pop();
    *sp++ = p;
    p->dim[0] = cols;
    p->size = cols * lhs_cols;
}

/*
    dmn is an input rows x cols array, with elements stored in column-major order.
    it is initialized from a standard data matrix (rows are stored
    in row-major order).
    Typical operations in this function iterate over the elements of
    a given row, and so it is convenient to have rows be contiguous.

    dm is a work vector of length rows.
    dn1, dn2, and dn3 are work vectors of length cols.
    in is an int work vector of length cols.

    d1 is the underlying data of the lhs (one or more column vectors to be estimated)
    d2 is the underlying data of the rhs (regression matrix)
 */
static int lsq(data* dmn, data* col_sumsq, data* dn2, data* dn3, data* dm, int* in,
               int rows, int cols, int lhs_cols,
               data* d1, data* d2)
{
    data *dp1, *dp2;
    float f1, f2, f3, f4;
    int i, j, k, l;

    printf("lsq rows %d, cols %d\n", rows, cols);
    dp1 = dmn;

    // populate work array col_sumsq with the sums of the
    // squares of the columns of dmn.
    //
    dp2 = col_sumsq;
    for (j = 0; j < cols; j++) {
        f1 = 0.;
        for (i = 0; i < rows; i++) {
            f2 = *dp1++;
            f1 += f2 * f2;
        }
        *dp2++ = f1;
    }

    pmat_T("col_sumsq (sum sq cols; +/[1]rhs X rhs)", col_sumsq, 1, cols);

    // initialize in[] to be [0, 1, .. cols-1]
    //
    for (j = 0; j < cols; j++) {
        in[j] = j;
    }

    for (int col = 0; col < cols; col++) {
        // find the index of the largest sum of squares
        // from "col" to the right.
        //
        f1 = col_sumsq[col];
        l = col;
        dp1 = col_sumsq + col + 1;
        for (j = col + 1; j < cols; j++) {
            if (fabs(f1) < fabs(*dp1++)) {
                f1 = dp1[-1];
                l = j;
            }
        }

        // if necessary, swap columns "l" and "col"
        if (l != col) {
            int tmp = in[col];
            in[col] = in[l];
            in[l] = tmp;

            data dtmp = col_sumsq[l];
            col_sumsq[l] = col_sumsq[col];
            col_sumsq[col] = dtmp;

            dp1 = dmn + col * rows;
            dp2 = dmn + l * rows;
            for (i = 0; i < rows; i++) {
                f1 = *dp1;
                *dp1++ = *dp2;
                *dp2++ = f1;
            }
        }

        dp1 = dmn + col * rows + col;
        data main_diag_elt = *dp1;

        pmat_T("dmn", dmn, rows, cols);
        printf("col %d, main diag elt %f\n", col, main_diag_elt);

        // f1 becomes sum_sq of elts at main diag and going down..
        f1 = 0.;
        for (i = col; i < rows; i++) {
            f2 = *dp1++;
            f1 += f2 * f2;
        }

        if (f1 == 0.)
            return (1);

        f2 = sqrt(f1);
        if (main_diag_elt >= 0.)
            f2 = -f2;

        dn2[col] = f2;

        f1 = 1. / (f1 - main_diag_elt * f2);

        // tweak main diagonal element..
        dmn[col * rows + col] = main_diag_elt - f2;

        for (j = col + 1; j < cols; j++) {
            f2 = 0.;
            dp1 = dmn + col * rows + col;
            dp2 = dmn + j * rows + col;
            for (i = col; i < rows; i++)
                f2 += *dp1++ * *dp2++;
            dn3[j] = f1 * f2;
        }

        // tweak elts to the right of the main diag..
        for (j = col + 1; j < cols; j++) {
            dp1 = dmn + col * rows + col;
            dp2 = dmn + j * rows + col;
            f1 = dn3[j];
            for (i = col; i < rows; i++)
                *dp2++ -= *dp1++ * f1;
            f1 = dmn[j * rows + col];
            col_sumsq[j] -= f1;
        }
    }

    for (k = 0; k < lhs_cols; k++) {
        // load the k'th left-hand side column vector into dm.
        dp1 = dm;
        l = k;
        for (i = 0; i < rows; i++) {
            *dp1++ = d1[l];
            l += lhs_cols;
        }
        solve(rows, cols, dmn, dn2, in, dm, dn3);
        l = k;

        dp1 = dm;
        for (i = 0; i < rows; i++) {
            f1 = -d1[l];
            l += lhs_cols;
            dp2 = dn3;
            for (j = 0; j < cols; j++)
                f1 += d2[i * cols + j] * *dp2++;
            *dp1++ = f1;
        }
        solve(rows, cols, dmn, dn2, in, dm, col_sumsq);

        f4 = 0.;
        f3 = 0.;
        dp1 = dn3;
        dp2 = col_sumsq;
        for (i = 0; i < cols; i++) {
            f1 = *dp1++;
            f4 += f1 * f1;
            f1 = *dp2++;
            f3 += f1 * f1;
        }

        if (f3 > 0.0625 * f4)
            return (1);
    loop:
        if (intflg)
            return (1);

        dp1 = dn3;
        dp2 = col_sumsq;
        for (i = 0; i < cols; i++)
            *dp1++ += *dp2++;

        if (f3 <= 4.81e-35 * f4)
            goto out;

        l = k;
        dp1 = dm;
        for (i = 0; i < rows; i++) {
            f1 = -d1[l];
            l += lhs_cols;
            dp2 = dn3;
            for (j = 0; j < cols; j++)
                f1 += d2[i * cols + j] * *dp2++;
            *dp1++ = f1;
        }

        solve(rows, cols, dmn, dn2, in, dm, col_sumsq);

        f2 = f3;
        f3 = 0.;
        dp1 = col_sumsq;
        for (i = 0; i < cols; i++) {
            f1 = *dp1++;
            f3 += f1 * f1;
        }

        if (f3 < 0.0625 * f2)
            goto loop;

    out:
        l = k;
        dp1 = dn3;
        for (i = 0; i < cols; i++) {
            d1[l] = *dp1++;
            l += lhs_cols;
        }
    }

    return (0);
}

/*
 m columns
 n rows
 dmn:  input array; rows x cols
 dm:   input vector; rows elements
 dn1:  in/out
 */
static void solve(int rows, int cols, data* dmn, data* dn2, int* in, data* dm, data* dn1)
{
    data *dp1, *dp2;
    int row, col, k;
    float f1;

    pmat_T("solve; dmn", dmn, rows, cols);
    pmat_T("solve; dm in", dm, rows, 1);
    pmat_T("solve; dn2", dn2, 1, cols);
    pmat_T("solve; dn1 in", dn1, 1, cols);

    for (col = 0; col < cols; col++) {
        // dp1 points at col'th main diagonal element..
        dp1 = dmn + col * rows + col;
        data main_diag_elt = *dp1;

        dp2 = dm + col;

        f1 = 0.;
        for (row = col; row < rows; row++)
            f1 += *dp1++ * *dp2++;

        f1 /= main_diag_elt * dn2[col];

        // dp1 points at col'th main diagonal element..
        dp1 = dmn + col * rows + col;

        // dp2 points at col'th element of dm..
        dp2 = dm + col;

        for (row = col; row < rows; row++)
            *dp2++ += f1 * *dp1++;
    }

    dp1 = dm + cols;
    dp2 = dn2 + cols;
    dn1[in[cols - 1]] = *--dp1 / *--dp2;
    for (row = cols - 2; row >= 0; row--) {
        f1 = -*--dp1;
        k = (row + 1) * rows + row;
        for (col = row + 1; col < cols; col++) {
            f1 += dmn[k] * dn1[in[col]];
            k += rows;
        }
        dn1[in[row]] = -f1 / *--dp2;
    }

    pmat_T("solve; dm out", dm, rows, 1);
    pmat_T("solve; dn1 out", dn1, 1, cols);
}

void pmat_T(char *title, data *elts, int rows, int cols) {
    printf("%s:\n", title);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            data elt = *(elts + col * rows + row);
            printf("%8.3f", elt);
        }
        printf("\n");
    }
    printf("\n");
}

void pmat(char *title, data *elts, int rows, int cols) {
    printf("%s:\n", title);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            data elt = *(elts + row * cols + col);
            printf("%8.3f", elt);
        }
        printf("\n");
    }
    printf("\n");
}

void pint(char *title, int *elts, int rows) {
    printf("%s:\n", title);

    for (int row = 0; row < rows; ++row) {
        printf("%8d", elts[row]);
    }

    printf("\n");
}
