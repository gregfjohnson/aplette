/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include <math.h>
#include "apl.h"
#include "data.h"
#include "utility.h"
#include "memory.h"

/*
   It looks like Ken Thompson (or whoever wrote this code) implemented
   the Householder reflector approach to solving linear systems.
   The idea is to take the M matrix, and upper-triangularize it by
   a series of left-multiplies by orthonormal matrices.
   We then apply the same series of multiplies to the Y vector to
   get a transformed linear system that is easy to solve, but which
   has the same solution as the original problem.

   We simply solve the mxm linear system via back-substitution.

   Here is an APL function that computes the Householder reflector:

   C@J Householder reflector
   C@J given a non-zero vector v, return an orthonormal matrix u
   C@J such that u +.X v is (len v) X x_axis
   C@J
   C@J The idea is to "stretch" x_axis to the length of v, and
   C@J then form the diagonal of a rhombus by adding v and the stretched x_axis.
   C@J we normalize the thus-formed diagonal of this rhombus.
   C@J we can project v onto this diagonal, and then go
   C@J that same distance a second time.  this will end us up
   C@J on the X axis, specifically at (len v) X x_axis.
   C@J
   Gz { hou x; xaxis; lenx; stretchxaxis; u; lenu; unorm; identmat
   x { ,x

   xaxis { (Rx) Y ,1

   lenx         { (x +.Xx) * .5
   stretchxaxis { xaxis X -lenx

   u { x + stretchxaxis

   lenu  { (u+.Xu) * .5
   unorm { u % lenu

   identmat { (IRx) J.= IRx
   z        { identmat - 2 X unorm J.X unorm
*/


static int lsq(data* dmn, data* dn1, data* dn2, data* vec2_cols, data* dm, int* in,
    int n, int m, int lhs_cols,
    data* d1, data* d2);

static void solve(int m, int n, data* dmn, data* dn2, int* in, data* dm, data* dn1);

static void pmat(char *title, data *elts, int rows, int cols);
static void pmat_cm(char *title, data *elts, int rows, int cols);
static void pint(char *title, int *elts, int rows);

void ex_ddom()
{
    struct item *p, *q;
    int row, col, m, rows, cols, lhs_cols, *in;
    data *d1, *dmn, *dn1, *dn2, *vec2_cols, *dm;
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

        // data array of dimension rows x cols; the input RHS matrix
        // containing the regression model.
        dmn = (data*)al;

        // data array of dimension cols
        dn1 = dmn + rows * cols;

        // data array of dimension cols
        dn2 = dn1 + cols;

        // data array of dimension cols
        vec2_cols = dn2 + cols;

        // data array of dimension rows;
        // used to hold the LHS vector(s) to be regressed against the model.
        dm = vec2_cols + cols;

        // int array of dimension cols; the columns of the regression model
        // matrix are permuted to improve numerical stability, and this
        // array contains the indices of the columns as they are swapped around.
        in = (int*)(dm + rows);

    #else
        dmn = (data*) alloc(rows*cols * SDAT);
        dn1 = (data*) alloc(cols * SDAT);
        dn2 = (data*) alloc(cols * SDAT);
        vec2_cols = (data*) alloc(cols * SDAT);
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

    pmat_cm("lsq dmn", dmn,rows,cols);
    int result = lsq(dmn, dn1, dn2, vec2_cols, dm, in, rows, cols, lhs_cols, p->datap, q->datap);
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
    vec1_cols, dn2, and vec2_cols are work vectors of length cols.
    in is an int work vector of length cols.

    lhs_data is the underlying data of the lhs (one or more column vectors to be estimated)
    rhs_data is the underlying data of the rhs (regression matrix)

    You can use orthonormal matrix operations on the nx1 lhs and the nxm rhs to get the
    rhs to be upper triangular.  Then, you can use simple back-substitution on this little
    mxm system to get the solution.

    Householder reflectors are a standard way of doing this.  Take for example the first
    column of rhs; call this vector x.  We desire Householder reflector U such that
    U x = len_x X [1, 0, .. 0]'.

    Let pi = sum_sq(X) / 2.
    Let u = x + len_x X [1, 0, .. 0]'

    then U = I - u u' / pi.

    It looks like this may be what the following code is doing.

    After conditioning the input nxm regression matrix as above, the algorithm regresses
    the system.  It calculates the residuals of this solution, and accepts the solution
    if the residuals are small enough.  If not, the the residual vector is regressed
    and the solution is added into the original solution.  this process is repeated until
    the result has acceptably small residuals.
 */
static int lsq(data* dmn, data* vec1_cols, data* dn2, data* vec2_cols, data* dm, int* in,
               int rows, int cols, int lhs_cols,
               data* lhs_data, data* rhs_data)
{
    data *dp1, *dp2;
    float f1, f2;
    int i, j, k, l;

    printf("lsq rows %d, cols %d\n", rows, cols);
    dp1 = dmn;

    // populate work array vec1_cols with the sums of the
    // squares of the columns of dmn.
    //
    dp2 = vec1_cols;
    for (j = 0; j < cols; j++) {
        data sum_sq = 0.;
        for (i = 0; i < rows; i++) {
            data tmp = *dp1++;
            sum_sq += tmp * tmp;
        }
        *dp2++ = sum_sq;
    }

    pmat_cm("vec1_cols (sum sq cols; +/[1]rhs X rhs)", vec1_cols, 1, cols);

    // initialize in[] to be [0, 1, .. cols-1]
    //
    for (j = 0; j < cols; j++) {
        in[j] = j;
    }

    for (int col = 0; col < cols; col++) {
        printf("col %d..\n", col);
        pmat_cm("dmn", dmn, rows, cols);
        pmat_cm("col sum_sq?", vec1_cols, 1, cols);

        // find the index of the largest sum of squares
        // from "col" to the right.
        //
        f1 = vec1_cols[col];

        l = col;
        dp1 = vec1_cols + col + 1;
        for (j = col + 1; j < cols; j++) {
            if (fabs(f1) < fabs(*dp1++)) {
                f1 = dp1[-1];
                l = j;
            }
        }

        // if necessary, swap columns "l" and "col" to
        // improve numerical stability.
        if (l != col) {
            int tmp = in[col];
            in[col] = in[l];
            in[l] = tmp;

            data dtmp = vec1_cols[l];
            vec1_cols[l] = vec1_cols[col];
            vec1_cols[col] = dtmp;

            dp1 = dmn + col * rows;
            dp2 = dmn + l * rows;
            for (i = 0; i < rows; i++) {
                data tmp = *dp1;
                *dp1++ = *dp2;
                *dp2++ = tmp;
            }
        }

        dp1 = dmn + col * rows + col;
        data main_diag_elt = *dp1;

        pmat_cm("dmn", dmn, rows, cols);
        printf("col %d, main diag elt %f\n", col, main_diag_elt);

        // column_tail_sumsq becomes sum_sq of elts at main diag and going down..
        data column_tail_sumsq = 0.;
        for (i = col; i < rows; i++) {
            data tmp = *dp1++;
            column_tail_sumsq += tmp * tmp;
        }

        if (column_tail_sumsq == 0.)
            return (1);

        data column_tail_len = sqrt(column_tail_sumsq);

        if (main_diag_elt >= 0.)
            column_tail_len = -column_tail_len;

        printf("length of vector at and below main diagonal:  %f\n", column_tail_len);

        // dn2 contains the L2 length of the vector at the main
        // diagonal and going downward from there.
        // (possibly negated.)
        dn2[col] = column_tail_len;
        pmat_cm("dmn so far", dmn, rows, col+1);
        pmat_cm("dn2 so far", dn2, 1, col+1);

        data pivot = 1. / (column_tail_sumsq - main_diag_elt * column_tail_len);

        // tweak main diagonal element..
        // increase absolute value of main diagonal element
        // by column tail length..
        dmn[col * rows + col] = main_diag_elt - column_tail_len;

        // calculate vec2_cols[] elements
        for (j = col + 1; j < cols; j++) {

            // calculate inner products of column tail vectors 
            // for current column col and columns to the right
            dp1 = dmn + col * rows + col;
            dp2 = dmn + j * rows + col;

            f2 = 0.;
            for (i = col; i < rows; i++)
                f2 += *dp1++ * *dp2++;

            // multiply inner product by pivot..
            vec2_cols[j] = pivot * f2;
        }

        // for columns to the right of current column,
        // and rows starting one below current column,
        // subtract current column times j'th vec2_cols[]
        // element calculated above..
        //
        // vec1_cols starts with the sums of the squares
        // of the columns of dmn.  ?? it gets updated to
        // maintain that invariant ??
        // 
        for (j = col + 1; j < cols; j++) {
            dp1 = dmn + col * rows + col;
            dp2 = dmn + j * rows + col;

            f1 = vec2_cols[j];
            for (i = col; i < rows; i++)
                *dp2++ -= *dp1++ * f1;

            vec1_cols[j] -= dmn[j * rows + col] * dmn[j * rows + col];
        }
    }

    #if 0
    { // as an experiment, zero out all below-diagonal elements of dmn..
      // didn't work.. ?!?
        printf("lsq rows %d, cols %d\n", rows, cols);
        for (int col = 0; col < cols; ++col) {
            for (int row = col+1; row < rows; ++row) {
                printf("do <%d %d> (data[%d])..\n", row, col, col * rows + row);
                dp1 = dmn + col * rows + row;
                printf("before:  %f\n", *dp1);
                *dp1 = 0.;
            }
        }
    }
    pmat_cm("zero below-diagonal elements of dmn", dmn, rows, cols);
    #endif

    pmat_cm("looping over lhs vectors; dmn", dmn, rows, cols);
    pmat_cm("dn2", dn2, 1, cols);

    for (int lhs_col = 0; lhs_col < lhs_cols; lhs_col++) {
        // load the lhs_col'th left-hand side column vector into dm.
        dp1 = dm;
        l = lhs_col;
        for (i = 0; i < rows; i++) {
            *dp1++ = lhs_data[l];
            l += lhs_cols;
        }
        data *solution = vec2_cols;

        solve(rows, cols, dmn, dn2, in, dm, solution);

        data soln_sumsq = 0.;
        dp1 = solution;
        for (i = 0; i < cols; i++) {
            data tmp = *dp1++;
            soln_sumsq += tmp * tmp;
        }

        // calculate model y_hat vector, and
        // subtract y, to form residual vector.
        // do regression on the residual vector,
        // and look at the sum of squares of the
        // solution.  if more than 1/16 the
        // sum of squares of the original solution
        // above, consider the system unsolvable
        // (columns of rhs matrix are not linearly
        // independent enough) and give up.
        //
        l = lhs_col;
        dp1 = dm;
        for (i = 0; i < rows; i++) {
            f1 = -lhs_data[l];
            l += lhs_cols;

            dp2 = solution;
            for (j = 0; j < cols; j++)
                f1 += rhs_data[i * cols + j] * *dp2++;

            *dp1++ = f1;
        }
        solve(rows, cols, dmn, dn2, in, dm, vec1_cols);

        float residual_soln_sum_sq = 0.;
        dp2 = vec1_cols;
        for (i = 0; i < cols; i++) {
            data tmp = *dp2++;
            residual_soln_sum_sq += tmp * tmp;
        }

        if (residual_soln_sum_sq > 0.0625 * soln_sumsq)
            return (1);
    loop:
        printf("loop..\n");

        if (intflg)
            return (1);

        // add residual solution into original solution
        // solution
        //
        dp1 = solution;
        dp2 = vec1_cols;
        for (i = 0; i < cols; i++)
            *dp1++ += *dp2++;

        if (residual_soln_sum_sq <= 4.81e-35 * soln_sumsq) {
            printf("exit loop..\n");
            goto out;
        }

        // put residuals based on solution in solution
        // into dm.
        //
        l = lhs_col;
        dp1 = dm;
        for (i = 0; i < rows; i++) {
            data f1 = -lhs_data[l];
            l += lhs_cols;

            dp2 = solution;
            for (j = 0; j < cols; j++)
                f1 += rhs_data[i * cols + j] * *dp2++;

            *dp1++ = f1;
        }

        solve(rows, cols, dmn, dn2, in, dm, vec1_cols);

        data prev_residual_soln_sum_sq = residual_soln_sum_sq;
        residual_soln_sum_sq = 0.;

        dp1 = vec1_cols;
        for (i = 0; i < cols; i++) {
            data tmp = *dp1++;
            residual_soln_sum_sq += tmp * tmp;
        }

        if (residual_soln_sum_sq < 0.0625 * prev_residual_soln_sum_sq) {
            printf("keep looping..\n");
            goto loop;

        } else {
            printf("fall out of loop..\n");
        }

    out:
        // copy the solution for this lhs column
        // into the corresponding column of the result array.
        l = lhs_col;
        dp1 = solution;
        for (i = 0; i < cols; i++) {
            lhs_data[l] = *dp1++;
            l += lhs_cols;
        }
    }

    return (0);
}

/*
 dmn:  input array; rows x cols; read-only.
 dn2:  input vector; cols elts; read-only.
 dm:   input vector; rows elements; updated in place as a work array.
 dn1:  output vector; cols elts
 */
static void solve(int rows, int cols, data* dmn, data* dn2, int* in, data* dm, data* dn1)
{
    data *dp1, *dp2;
    int row, col, k;
    float f1;

    memset(dn1, 0, cols*sizeof(data));

    pmat_cm("solve; dmn in", dmn, rows, cols);
    pmat_cm("solve; dn2 in", dn2, 1, cols);
    pmat_cm("solve; dm in", dm, rows, 1);

    //
    // going through elements left to right,
    // add into tail of dm the tail of dmn[;col]
    // multiplied by inner product of those
    // vectors divided by (dmn[col;col] X dn2[col]).
    //
    /*
        Lio { 0
        rows { R dm
        indices { col + I (rows - col)

        num { dm[indices] +.X dnm[indices; col]
        den { dn2[col]     X  dnm[col; col]

        dm[indices] { dm[indices] + dnm[indices; col] X num % den
     */
    for (col = 0; col < cols; col++) {
        // dp1 points at col'th main diagonal element..
        data *dmn_ptr = dmn + col * rows + col;
        data main_diag_elt = *dmn_ptr;

        data *dm_ptr = dm + col;

        // form inner product of tail of dm and tail
        // of col'th row of dmn.
        f1 = 0.;
        for (row = col; row < rows; row++)
            f1 += *dmn_ptr++ * *dm_ptr++;

        // calculate pivot multiplier
        f1 /= main_diag_elt * dn2[col];

        // dmn_ptr points at col'th main diagonal element..
        dmn_ptr = dmn + col * rows + col;

        // dm_ptr points at col'th element of dm..
        dm_ptr = dm + col;

        // update tail of dm with f1 times tail of
        // col'th row of dmn.
        for (row = col; row < rows; row++)
            *dm_ptr++ += f1 * *dmn_ptr++;
    }
    // pmat_cm("solve; dm after massage", dm, rows, 1);

    // work backward through columns..
    // it looks like we treat dmn as upper-triangular
    // and solve from the last equation up.
    //
    // we treat dn2[] as if they were the elements of
    // the main diagonal of dmn.
    //
    // have m =     a<k> x<k> + .. + a<n-1> x<n-1>,
    // and we know x<k+1> .. x<n-1>.
    // we form m - a<k+1> x<k+1> - .. - a<n-1> x<n-1>.
    // then, we divide by dn2[k] instead of dnm[k;k]
    // for some reason.
    //
    data *dm_ptr  = dm + cols;
    data *dn2_ptr = dn2 + cols;

    // last element of solution is dm[cols-1] / dn2[cols-1]..
    //
    dn1[in[cols - 1]] = *--dm_ptr / *--dn2_ptr;

    for (col = cols - 2; col >= 0; col--) {
        f1 = *--dm_ptr;
        k = (col + 1) * rows + col;
        for (int col2 = col + 1; col2 < cols; col2++) {
            f1 -= dmn[k] * dn1[in[col2]];
            k += rows;
        }
        dn1[in[row]] = f1 / *--dn2_ptr;
    }

    pmat_cm("solve; dn1 out", dn1, 1, cols);
}

void pmat_cm_apl(data *elts, int rows, int cols) {
    printf("%d %d R ", rows, cols);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            data elt = *(elts + col * rows + row);
            if (elt < 0) {
                printf("`");
                elt = -elt;
                printf("%-7.3f", elt);
            } else {
                printf("%-8.3f", elt);
            }
        }
    }
    printf("\n");
}

// print the matrix; elts are in column-major order.
//
void pmat_cm(char *title, data *elts, int rows, int cols) {
    printf("%s:\n", title);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            data elt = *(elts + col * rows + row);
            printf("%8.3f", elt);
        }
        printf("\n");
    }
    pmat_cm_apl(elts, rows, cols);
    printf("\n");
}

// print the matrix; elts are in standard row-major order.
//
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
