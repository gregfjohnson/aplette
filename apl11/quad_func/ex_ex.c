#include "apl.h"
#include "data.h"
#include "utility.h"
#include "char.h"


void ex_ex(void)
{
   struct nlist *np;
   struct item *p, *ip;
   int i, nlen;
   int j, n;
   char buf[40];

   p = fetch1();
   if(p->type != CH) error(ERR_domain,"");
   if(p->rank > 2) error(ERR_rank,"");
   if(p->rank < 2) {n=1; nlen=p->size;}
   else {n=p->dim[0]; nlen=p->dim[1];}
   if(nlen>=40) error(ERR_length,"");
   ip=newdat(DA,1,n);

   for(j=0;j<n;j++){
      copy(CH, ((char *)p->datap)+nlen*j, buf, nlen);
      buf[nlen] = 0;
      for(i=nlen-1;buf[i]==' ';i--) buf[i]=0;
      np = nlook(buf);
      i = 0;
      if(np != 0) {
         if(np->use==MF||
            np->use==NF||
            np->use==DF||
            np->use==DA||
            np->use==CH||
            np->use==LV) {erase(np); i=1;}
      }
      ip->datap[j] = i;
   }
   pop();
   *sp++ = ip;
}

