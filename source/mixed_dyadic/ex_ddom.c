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
    int n, int m, int p,
    data* d1, data* d2);

static void solve(int m, int n, data* dmn, data* dn2, int* in, data* dm, data* dn1);

void ex_ddom()
{
    struct item *p, *q;
    int a, b, m, n, o, *in;
    data *d1, *dmn, *dn1, *dn2, *dn3, *dm;
    char* al;

    p = fetch2();
    q = sp[-2];
    if (p->itemType != DA || q->itemType != DA)
        error(ERR_domain, "domino - incorrect types");
    if ((p->rank != 1 && p->rank != 2) || q->rank != 2)
        error(ERR_rank, "domino - unexpected ranks");
    m = q->dim[0];
    n = q->dim[1];
    if (m < n || m != p->dim[0])
        error(ERR_rank, "domino - mismatch");
    o = 1;
    if (p->rank == 2)
        o = p->dim[1];
    al = (char*)alloc(n * (SINT + SDAT * m + SDAT * 3) + SDAT * m);
    if (al == 0)
        error(ERR, "domino - unable to allocate memory");
    dmn = (data*)al;
    dn1 = dmn + m * n;
    dn2 = dn1 + n;
    dn3 = dn2 + n;
    dm = dn3 + n;
    in = (int*)(dm + m);
    d1 = q->datap;
    for (b = 0; b < m; b++) {
        for (a = 0; a < n; a++)
            dmn[a * m + b] = *d1++;
    }
    a = lsq(dmn, dn1, dn2, dn3, dm, in, m, n, o, p->datap, q->datap);
    aplfree((int*)dmn);
    if (a)
        error(ERR, "domino - could not solve");
    sp--;
    pop();
    *sp++ = p;
    p->dim[0] = n;
    p->size = n * o;
}

static int lsq(data* dmn, data* dn1, data* dn2, data* dn3, data* dm, int* in,
    int m, int n, int p,
    data* d1, data* d2)
{
    data *dp1, *dp2;
    double f1, f2, f3, f4;
    int i, j, k, l;

    dp1 = dmn;
    dp2 = dn1;
    for (j = 0; j < n; j++) {
        f1 = 0.;
        for (i = 0; i < m; i++) {
            f2 = *dp1++;
            f1 += f2 * f2;
        }
        *dp2++ = f1;
        in[j] = j;
    }
    for (k = 0; k < n; k++) {
        f1 = dn1[k];
        l = k;
        dp1 = dn1 + k + 1;
        for (j = k + 1; j < n; j++) {
            if (f1 < *dp1++) {
                f1 = dp1[-1];
                l = j;
            }
        }
        if (l != k) {
            i = in[k];
            in[k] = in[l];
            in[l] = i;
            dn1[l] = dn1[k];
            dn1[k] = f1;
            dp1 = dmn + k * m;
            dp2 = dmn + l * m;
            for (i = 0; i < m; i++) {
                f1 = *dp1;
                *dp1++ = *dp2;
                *dp2++ = f1;
            }
        }
        f1 = 0.;
        dp1 = dmn + k * m + k;
        f3 = *dp1;
        for (i = k; i < m; i++) {
            f2 = *dp1++;
            f1 += f2 * f2;
        }
        if (f1 == 0.)
            return (1);
        f2 = sqrt(f1);
        if (f3 >= 0.)
            f2 = -f2;
        dn2[k] = f2;
        f1 = 1. / (f1 - f3 * f2);
        dmn[k * m + k] = f3 - f2;
        for (j = k + 1; j < n; j++) {
            f2 = 0.;
            dp1 = dmn + k * m + k;
            dp2 = dmn + j * m + k;
            for (i = k; i < m; i++)
                f2 += *dp1++ * *dp2++;
            dn3[j] = f1 * f2;
        }
        for (j = k + 1; j < n; j++) {
            dp1 = dmn + k * m + k;
            dp2 = dmn + j * m + k;
            f1 = dn3[j];
            for (i = k; i < m; i++)
                *dp2++ -= *dp1++ * f1;
            f1 = dmn[j * m + k];
            dn1[j] -= f1;
        }
    }
    for (k = 0; k < p; k++) {
        dp1 = dm;
        l = k;
        for (i = 0; i < m; i++) {
            *dp1++ = d1[l];
            l += p;
        }
        solve(m, n, dmn, dn2, in, dm, dn3);
        l = k;
        dp1 = dm;
        for (i = 0; i < m; i++) {
            f1 = -d1[l];
            l += p;
            dp2 = dn3;
            for (j = 0; j < n; j++)
                f1 += d2[i * n + j] * *dp2++;
            *dp1++ = f1;
        }
        solve(m, n, dmn, dn2, in, dm, dn1);
        f4 = 0.;
        f3 = 0.;
        dp1 = dn3;
        dp2 = dn1;
        for (i = 0; i < n; i++) {
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
        dp2 = dn1;
        for (i = 0; i < n; i++)
            *dp1++ += *dp2++;
        if (f3 <= 4.81e-35 * f4)
            goto out;
        l = k;
        dp1 = dm;
        for (i = 0; i < m; i++) {
            f1 = -d1[l];
            l += p;
            dp2 = dn3;
            for (j = 0; j < n; j++)
                f1 += d2[i * n + j] * *dp2++;
            *dp1++ = f1;
        }
        solve(m, n, dmn, dn2, in, dm, dn1);
        f2 = f3;
        f3 = 0.;
        dp1 = dn1;
        for (i = 0; i < n; i++) {
            f1 = *dp1++;
            f3 += f1 * f1;
        }
        if (f3 < 0.0625 * f2)
            goto loop;
    out:
        l = k;
        dp1 = dn3;
        for (i = 0; i < n; i++) {
            d1[l] = *dp1++;
            l += p;
        }
    }
    return (0);
}

static void solve(int m, int n, data* dmn, data* dn2, int* in, data* dm, data* dn1)
{
    data *dp1, *dp2;
    int i, j, k;
    double f1, f2;

    for (j = 0; j < n; j++) {
        f1 = 0.;
        dp1 = dmn + j * m + j;
        dp2 = dm + j;
        f2 = *dp1;
        for (i = j; i < m; i++)
            f1 += *dp1++ * *dp2++;
        f1 /= f2 * dn2[j];
        dp1 = dmn + j * m + j;
        dp2 = dm + j;
        for (i = j; i < m; i++)
            *dp2++ += f1 * *dp1++;
    }
    dp1 = dm + n;
    dp2 = dn2 + n;
    dn1[in[n - 1]] = *--dp1 / *--dp2;
    for (i = n - 2; i >= 0; i--) {
        f1 = -*--dp1;
        k = (i + 1) * m + i;
        for (j = i + 1; j < n; j++) {
            f1 += dmn[k] * dn1[in[j]];
            k += m;
        }
        dn1[in[i]] = -f1 / *--dp2;
    }
}
