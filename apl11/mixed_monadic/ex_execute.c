/* Copyright U S WEST Advanced Technologies, Inc.
 * You may use, copy, modify and sublicense this Software
 * subject to the conditions expressed in the file "License".
 */

#include "apl.h"
#include "data.h"
#include "utility.h"
#include "memory.h"

/* the primitive function "execute" (uptack jot) */
void ex_execute() {
struct item *p;
int i, j, dim0, dim1;
char *b;
struct Context *thisContext;

   p = fetch1();
   if ( p->rank > 2 ) error(ERR_rank,"");
   if ( p->type != CH ) error(ERR_domain,"not a literal value");
   /*get out if nothing to do, apr 2-23-77 */
   if (p->size == 0) return;

   b = (char *)p->datap;
   dim0 = p->rank < 2 ? 1       : p->dim[0];
   dim1 = p->rank < 2 ? p->size : p->dim[1];


   thisContext=(struct Context *)alloc(sizeof(struct Context));
   thisContext->prev = gsip;            /* setup new context */
   thisContext->text = (char *)alloc( dim1+1 );
   thisContext->Mode = exec;
   thisContext->sp = sp;
   thisContext->suspended = 0;
   gsip = thisContext;

   for ( i=0; i<dim0 ; i++) {
      copy(CH, b, gsip->text, dim1);
      gsip->text[dim1] = '\n';
      compile_new(1);

      if(gsip->pcode != 0){
         gsip->ptr=gsip->pcode;
     gsip->sp=sp;
         execute();
         aplfree((int *) gsip->pcode);
     if(gsip->sp == sp ) ex_nilret();
      }
      else {
         gsip = thisContext->prev;      /* restore previous context */
         aplfree((int *) thisContext->text);
         aplfree((int *) thisContext);

         error(ERR_implicit,"");
      }
      b += dim1;
      if(i < dim0-1) pop();
   }
   aplfree((int *) thisContext->text);
   gsip = thisContext->prev;      /* restore previous context */
   aplfree((int *) thisContext);
   p = *--sp;
   pop();
   *sp++ = p;
}
