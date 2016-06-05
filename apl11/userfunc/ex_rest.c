/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"

void ex_rest() {
   struct item *p;
   struct nlist *np;

   p = sp[-1];
   /*
    * the following is commented out because
    * of an obscure bug in the parser, which is
    * too difficult to correct right now.
    * the bug is related to the way the
    * "fn epilog" is compiled.  To accomodate labels,
    * it was kludged up to have the label restoration
    * code added after the entire fn was parsed.  A problem
    * is that the generated code is like:
    *
    * "rest-lab1 rest-lab2 eol rval-result rest-arg1 ..."
    *
    * the "eol rval-result" pops off the previous result, and
    * puts a "fetched" version of the returned value (result)
    * onto the stack.  The bug is that the "eol rval." should
    * be output at the beginning of the fn epilog.
    * The following two lines used to be a simple
    * "p = fetch(p)", which is used to disallow
    * a fn to return a LV, (by fetching it, it gets
    * converted to a RVAL.)  Since we later added
    * code which returned stuff which could not be
    * fetched (the DU, dummy datum, for example),
    * this thing had to be eliminated.  An earlier
    * version only fetched LV's, but that was eliminated
    * by adding the "RVAL" operator.  The test below
    * was made a botch, because no LV's should ever be
    * passed back.  However, for this to be true, the
    * "eol" should be executed first, so that any possible
    * LV's left around by the last line executed are
    * discarded.  Since we have some "rest"s in the epilog
    * before the eol, the following test fails.
    * I can't think of why it won't work properly as it
    * is, but if I had the time, I'd fix it properly.
    *   --jjb
   if(p->type == LV) error(ERR_botch,"rest B");
    */
   gsip->ptr += copy(IN, (char *) gsip->ptr, (char *) &np, 1);
   erase(np);
   np->itemp = sp[-2];
   np->use = 0;
   if(np->itemp) np->use = DA;
   sp--;
   sp[-1] = p;
}
