/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */
#include "apl.h"
#include "utility.h"
#include "data.h"

ex_rot0()
{
	fetch2();
	rotk(0);
}

ex_rotk()
{
	int k;

	k = topfix() - iorigin;
	fetch2();
	rotk(k);
}

ex_rot()
{
	struct item *p;

	fetch2();
	p = sp[-2];
	rotk(p->rank-1);
}

rotk(k)
{
	struct item *p, *q;
	int param, rot1();

	p = sp[-1];
	bidx(sp[-2]);
	if(k < 0 || k >= idx.rank) error(ERR_index,"");
	param = 0;
	colapse(k);
	if(idx.size != p->size) {
		if(p->size != 1) error(ERR_length,"");
		param++;
		datum = getdat(p);
	}
	p = newdat(idx.type, 1, idx.dimk);
	*sp++ = p;
	forloop(rot1, param);
	pop();
	pop();
}

rot1(param)
{
	struct item *p, *q;
	int i;
	int o, n;

	if(param == 0) datum = getdat(sp[-2]);
	o = fix(datum);
	if(o < 0) o = idx.dimk - (-o % idx.dimk);
	q = sp[-1];
	p = sp[-3];
	q->index = 0;
	n = access();
	for(i=0; i<idx.dimk; i++) {
		p->index = n + (o%idx.dimk)*idx.delk;
		putdat(q, getdat(p));
		o++;
	}
	for(i=0; i<idx.dimk; i++) {
		p->index = n;
		putdat(p, getdat(q));
		n += idx.delk;
	}
}
